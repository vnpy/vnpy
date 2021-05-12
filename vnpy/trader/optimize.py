from typing import Dict, List, Callable, Tuple
from itertools import product
from concurrent.futures import ProcessPoolExecutor
from random import random, choice
from time import perf_counter

from deap import creator, base, tools, algorithms
from numpy.core.einsumfunc import _update_other_results


class OptimizationSetting:
    """
    Setting for runnning optimization.
    """

    def __init__(self):
        """"""
        self.params = {}
        self.target_name = ""

    def add_parameter(
        self, name: str, start: float, end: float = None, step: float = None
    ):
        """"""
        if not end and not step:
            self.params[name] = [start]
            return

        if start >= end:
            print("参数优化起始点必须小于终止点")
            return

        if step <= 0:
            print("参数优化步进必须大于0")
            return

        value = start
        value_list = []

        while value <= end:
            value_list.append(value)
            value += step

        self.params[name] = value_list

    def set_target(self, target_name: str):
        """"""
        self.target_name = target_name

    def generate_setting(self):
        """"""
        keys = self.params.keys()
        values = self.params.values()
        products = list(product(*values))

        settings = []
        for p in products:
            setting = dict(zip(keys, p))
            settings.append(setting)

        return settings

    def generate_setting_ga(self):
        """"""
        settings_ga = []
        settings = self.generate_setting()
        for d in settings:
            param = [tuple(i) for i in d.items()]
            settings_ga.append(param)
        return settings_ga


def run_bf_optimization(
    optimization_func: Callable,
    optimization_setting: OptimizationSetting,
    key_func: callable,
    max_workers: int = None
) -> List[Tuple]:
    """Run brutal force optimization"""
    with ProcessPoolExecutor(max_workers) as executor:
        settings: List[Dict] = optimization_setting.generate_setting()
        results: List[Tuple] = list(executor.map(optimization_func, settings))
        results.sort(reverse=True, key=key_func)
        return results


def run_ga_optimization(
    optimization_func: Callable,
    optimization_setting: OptimizationSetting,
    key_func: callable,
    max_workers: int = None,
    population_size: int = 100,
    ngen_size: int = 30
) -> List[Tuple]:
    """Run genetic algorithm optimization"""
    # Create individual class
    if not hasattr(creator, "Individual"):
        creator.create("FitnessMax", base.Fitness, weights=(1.0,))
        creator.create("Individual", list, fitness=creator.FitnessMax)

    # Define functions for generate parameter randomly
    settings: List[Dict] = optimization_setting.generate_setting_ga()
    cache: Dict[Tuple, float] = {}

    def generate_parameter() -> list:
        """"""
        return choice(settings)

    def mutate_individual(individual: list, indpb: float) -> tuple:
        """"""
        size = len(individual)
        paramlist = generate_parameter()
        for i in range(size):
            if random() < indpb:
                individual[i] = paramlist[i]
        return individual,

    def ga_optimize(parameters: list) -> float:
        """"""
        tp: tuple = tuple(parameters)
        if tp in cache:
            result = cache[tp]
        else:
            setting: dict = dict(parameters)
            result: dict = optimization_func(setting)
            cache[tp] = result

        value: float = key_func(result)
        return (value, )

    # Set up genetic algorithm
    toolbox = base.Toolbox()
    toolbox.register("individual", tools.initIterate, creator.Individual, generate_parameter)
    toolbox.register("population", tools.initRepeat, list, toolbox.individual)
    toolbox.register("mate", tools.cxTwoPoint)
    toolbox.register("mutate", mutate_individual, indpb=1)
    toolbox.register("evaluate", ga_optimize)
    toolbox.register("select", tools.selNSGA2)

    total_size = len(settings)
    pop_size = population_size                      # number of individuals in each generation
    lambda_ = pop_size                              # number of children to produce at each generation
    mu = int(pop_size * 0.8)                        # number of individuals to select for the next generation

    cxpb = 0.95         # probability that an offspring is produced by crossover
    mutpb = 1 - cxpb    # probability that an offspring is produced by mutation
    ngen = ngen_size    # number of generation

    pop = toolbox.population(pop_size)

    # Run ga optimization
    print(f"参数优化空间：{total_size}")
    print(f"每代族群总数：{pop_size}")
    print(f"优良筛选个数：{mu}")
    print(f"迭代次数：{ngen}")
    print(f"交叉概率：{cxpb:.0%}")
    print(f"突变概率：{mutpb:.0%}")

    start = perf_counter()

    algorithms.eaMuPlusLambda(
        pop,
        toolbox,
        mu,
        lambda_,
        cxpb,
        mutpb,
        ngen
    )

    end = perf_counter()
    cost = int((end - start))

    print(f"遗传算法优化完成，耗时{cost}秒")

    results: list = list(cache.values())
    results.sort(reverse=True, key=key_func)
    return results
