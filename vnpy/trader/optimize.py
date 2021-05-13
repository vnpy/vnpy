from typing import Dict, List, Callable, Tuple
from itertools import product
from concurrent.futures import ProcessPoolExecutor
from random import random, choice
from time import perf_counter
from multiprocessing import Manager, Pool

from deap import creator, base, tools, algorithms


OUTPUT_FUNC = Callable[[str], None]
EVALUATE_FUNC = Callable[[dict], dict]
KEY_FUNC = Callable[[list], float]


# Create individual class used in genetic algorithm optimization
creator.create("FitnessMax", base.Fitness, weights=(1.0,))
creator.create("Individual", list, fitness=creator.FitnessMax)


class OptimizationSetting:
    """
    Setting for runnning optimization.
    """

    def __init__(self) -> None:
        """"""
        self.params: Dict[str, List] = {}
        self.target_name: str = ""

    def add_parameter(
        self,
        name: str,
        start: float,
        end: float = None,
        step: float = None
    ) -> None:
        """"""
        if end is None and step is None:
            self.params[name] = [start]
            return

        if start >= end:
            print("参数优化起始点必须小于终止点")
            return

        if step <= 0:
            print("参数优化步进必须大于0")
            return

        value: float = start
        value_list: List[float] = []

        while value <= end:
            value_list.append(value)
            value += step

        self.params[name] = value_list

    def set_target(self, target_name: str) -> None:
        """"""
        self.target_name = target_name

    def generate_setting(self) -> List[dict]:
        """"""
        keys = self.params.keys()
        values = self.params.values()
        products = list(product(*values))

        settings = []
        for p in products:
            setting = dict(zip(keys, p))
            settings.append(setting)

        return settings


def check_optimization_setting(
    optimization_setting: OptimizationSetting,
    output: OUTPUT_FUNC = print
) -> bool:
    """"""
    if not optimization_setting.generate_setting():
        output("优化参数组合为空，请检查")
        return False

    if not optimization_setting.target_name:
        output("优化目标未设置，请检查")
        return False

    return True


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
    # Define functions for generate parameter randomly
    buf: List[Dict] = optimization_setting.generate_setting()
    settings: List[Tuple] = [list(d.items()) for d in buf]

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

    # Set up multiprocessing Pool and Manager
    with Manager() as manager, Pool(max_workers) as pool:
        # Create shared dict for result cache
        cache: Dict[Tuple, Tuple] = manager.dict()

        # Set up toolbox
        toolbox = base.Toolbox()
        toolbox.register("individual", tools.initIterate, creator.Individual, generate_parameter)
        toolbox.register("population", tools.initRepeat, list, toolbox.individual)
        toolbox.register("mate", tools.cxTwoPoint)
        toolbox.register("mutate", mutate_individual, indpb=1)
        toolbox.register("select", tools.selNSGA2)
        toolbox.register("map", pool.map)
        toolbox.register(
            "evaluate",
            ga_optimize,
            cache,
            optimization_func,
            key_func
        )

        total_size: int = len(settings)
        pop_size: int = population_size                      # number of individuals in each generation
        lambda_: int = pop_size                              # number of children to produce at each generation
        mu: int = int(pop_size * 0.8)                        # number of individuals to select for the next generation

        cxpb: float = 0.95         # probability that an offspring is produced by crossover
        mutpb: float = 1 - cxpb    # probability that an offspring is produced by mutation
        ngen: int = ngen_size    # number of generation

        pop: list = toolbox.population(pop_size)

        # Run ga optimization
        print(f"参数优化空间：{total_size}")
        print(f"每代族群总数：{pop_size}")
        print(f"优良筛选个数：{mu}")
        print(f"迭代次数：{ngen}")
        print(f"交叉概率：{cxpb:.0%}")
        print(f"突变概率：{mutpb:.0%}")

        start: int = perf_counter()

        algorithms.eaMuPlusLambda(
            pop,
            toolbox,
            mu,
            lambda_,
            cxpb,
            mutpb,
            ngen
        )

        end: int = perf_counter()
        cost: int = int((end - start))

        print(f"遗传算法优化完成，耗时{cost}秒")

        results: list = list(cache.values())
        results.sort(reverse=True, key=key_func)
        return results


def ga_optimize(
    cache: dict,
    optimization_func: callable,
    key_func: callable,
    parameters: list
) -> float:
    """
    Functions to be run in genetic algorithm optimization.
    """
    tp: tuple = tuple(parameters)
    if tp in cache:
        result: tuple = cache[tp]
    else:
        setting: dict = dict(parameters)
        result: dict = optimization_func(setting)
        cache[tp] = result

    value: float = key_func(result)
    return (value, )
