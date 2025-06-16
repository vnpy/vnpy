from collections.abc import Callable
from itertools import product
from concurrent.futures import ProcessPoolExecutor
from random import random, choice
from time import perf_counter
from multiprocessing import get_context
from multiprocessing.context import BaseContext
from multiprocessing.managers import DictProxy
from _collections_abc import dict_keys, dict_values, Iterable

from tqdm import tqdm
from deap import creator, base, tools, algorithms       # type: ignore

from .locale import _

OUTPUT_FUNC = Callable[[str], None]
EVALUATE_FUNC = Callable[[dict], dict]
KEY_FUNC = Callable[[tuple], float]


# Create individual class used in genetic algorithm optimization
creator.create("FitnessMax", base.Fitness, weights=(1.0,))
creator.create("Individual", list, fitness=creator.FitnessMax)


class OptimizationSetting:
    """
    Setting for runnning optimization.
    """

    def __init__(self) -> None:
        """"""
        self.params: dict[str, list] = {}
        self.target_name: str = ""

    def add_parameter(
        self,
        name: str,
        start: float,
        end: float | None = None,
        step: float | None = None
    ) -> tuple[bool, str]:
        """"""
        if end is None or step is None:
            self.params[name] = [start]
            return True, _("固定参数添加成功")

        if start >= end:
            return False, _("参数优化起始点必须小于终止点")

        if step <= 0:
            return False, _("参数优化步进必须大于0")

        value: float = start
        value_list: list[float] = []

        while value <= end:
            value_list.append(value)
            value += step

        self.params[name] = value_list

        return True, _("范围参数添加成功，数量{}").format(len(value_list))

    def set_target(self, target_name: str) -> None:
        """"""
        self.target_name = target_name

    def generate_settings(self) -> list[dict]:
        """"""
        keys: dict_keys = self.params.keys()
        values: dict_values = self.params.values()
        products: list = list(product(*values))

        settings: list = []
        for p in products:
            setting: dict = dict(zip(keys, p, strict=False))
            settings.append(setting)

        return settings


def check_optimization_setting(
    optimization_setting: OptimizationSetting,
    output: OUTPUT_FUNC = print
) -> bool:
    """"""
    if not optimization_setting.generate_settings():
        output(_("优化参数组合为空，请检查"))
        return False

    if not optimization_setting.target_name:
        output(_("优化目标未设置，请检查"))
        return False

    return True


def run_bf_optimization(
    evaluate_func: EVALUATE_FUNC,
    optimization_setting: OptimizationSetting,
    key_func: KEY_FUNC,
    max_workers: int | None = None,
    output: OUTPUT_FUNC = print
) -> list[tuple]:
    """Run brutal force optimization"""
    settings: list[dict] = optimization_setting.generate_settings()

    output(_("开始执行穷举算法优化"))
    output(_("参数优化空间：{}").format(len(settings)))

    start: float = perf_counter()

    with ProcessPoolExecutor(
        max_workers,
        mp_context=get_context("spawn")
    ) as executor:
        it: Iterable = tqdm(
            executor.map(evaluate_func, settings),
            total=len(settings)
        )
        results: list[tuple] = list(it)
        results.sort(reverse=True, key=key_func)

        end: float = perf_counter()
        cost: int = int(end - start)
        output(_("穷举算法优化完成，耗时{}秒").format(cost))

        return results


def run_ga_optimization(
    evaluate_func: EVALUATE_FUNC,
    optimization_setting: OptimizationSetting,
    key_func: KEY_FUNC,
    max_workers: int | None = None,
    pop_size: int = 100,                    # population size: number of individuals in each generation
    ngen: int = 30,                         # number of generations: number of generations to evolve
    mu: int | None = None,                  # mu: number of individuals to select for the next generation
    lambda_: int | None = None,             # lambda: number of children to produce at each generation
    cxpb: float = 0.95,                     # crossover probability: probability that an offspring is produced by crossover
    mutpb: float | None = None,             # mutation probability: probability that an offspring is produced by mutation
    indpb: float = 1.0,                     # independent probability: probability for each gene to be mutated
    output: OUTPUT_FUNC = print,
) -> list[tuple]:
    """Run genetic algorithm optimization"""
    # Define functions for generate parameter randomly
    settings: list[dict] = optimization_setting.generate_settings()
    parameter_tuples: list[list[tuple]] = [list(d.items()) for d in settings]

    def generate_parameter() -> list:
        """"""
        return choice(parameter_tuples)

    def mutate_individual(individual: list, indpb: float) -> tuple:
        """"""
        size: int = len(individual)
        paramlist: list = generate_parameter()
        for i in range(size):
            if random() < indpb:
                individual[i] = paramlist[i]
        return individual,

    # Set up multiprocessing Pool and Manager
    ctx: BaseContext = get_context("spawn")
    with ctx.Manager() as manager, ctx.Pool(max_workers) as pool:
        # Create shared dict for result cache
        cache: DictProxy[tuple, tuple] = manager.dict()

        # Set up toolbox
        toolbox: base.Toolbox = base.Toolbox()
        toolbox.register("individual", tools.initIterate, creator.Individual, generate_parameter)
        toolbox.register("population", tools.initRepeat, list, toolbox.individual)
        toolbox.register("mate", tools.cxTwoPoint)
        toolbox.register("mutate", mutate_individual, indpb=indpb)
        toolbox.register("select", tools.selNSGA2)
        toolbox.register("map", pool.map)
        toolbox.register(
            "evaluate",
            ga_evaluate,
            cache,
            evaluate_func,
            key_func
        )

        # Set default values for DEAP parameters if not specified
        if mu is None:
            mu = int(pop_size * 0.8)

        if lambda_ is None:
            lambda_ = pop_size

        if mutpb is None:
            mutpb = 1.0 - cxpb

        total_size: int = len(parameter_tuples)
        pop: list = toolbox.population(pop_size)

        # Run ga optimization
        output(_("开始执行遗传算法优化"))
        output(_("参数优化空间：{}").format(total_size))
        output(_("每代族群总数：{}").format(pop_size))
        output(_("优良筛选个数：{}").format(mu))
        output(_("迭代次数：{}").format(ngen))
        output(_("交叉概率：{:.0%}").format(cxpb))
        output(_("突变概率：{:.0%}").format(mutpb))
        output(_("个体突变概率：{:.0%}").format(indpb))

        start: float = perf_counter()

        algorithms.eaMuPlusLambda(
            pop,
            toolbox,
            mu,
            lambda_,
            cxpb,
            mutpb,
            ngen,
            verbose=True
        )

        end: float = perf_counter()
        cost: int = int(end - start)

        output(_("遗传算法优化完成，耗时{}秒").format(cost))

        results: list = list(cache.values())
        results.sort(reverse=True, key=key_func)
        return results


def ga_evaluate(
    cache: dict,
    evaluate_func: Callable,
    key_func: Callable,
    parameters: list
) -> tuple[float, ]:
    """
    Functions to be run in genetic algorithm optimization.
    """
    tp: tuple = tuple(parameters)
    if tp in cache:
        result: dict = cache[tp]
    else:
        setting: dict = dict(parameters)
        result = evaluate_func(setting)
        cache[tp] = result

    value: float = key_func(result)
    return (value, )
