"""
support for asyncio
If you use this module, call async_executor.start() at startup.
and call async_executor.stop() at cleanup.
call async_executor.join() if you want to wait until it exit.
"""
import asyncio
import threading
from typing import Coroutine, Iterable, Union


class AsyncExecutor:

    def __init__(self):
        self.loop = asyncio.new_event_loop()
        self._thread = threading.Thread(target=self._exec)

    def start(self):
        self._thread.start()

    def stop(self):
        self.loop.stop()

    def join(self):
        self._thread.join()

    def _exec(self):
        self.loop.call_soon(lambda: None)
        self.loop.run_forever()


class SyncWrapper:
    wrapper_loop = asyncio.new_event_loop()

    def __init__(self, co: Coroutine):
        self.co = co
        self.result = None

    def __call__(self, *args, **kwargs):
        if self.result is None:
            try:
                if loop is asyncio.get_running_loop():
                    # fucking shit
                    self.schedule_new_coroutine()
                else:
                    self.schedule_coroutine()
            except RuntimeError:
                self.schedule_coroutine()
        return self.result

    def schedule_coroutine(self):
        task = asyncio.run_coroutine_threadsafe(self.co, loop=loop)
        self.result = task.result()

    def schedule_new_coroutine(self):
        thread = threading.Thread(target=self.run)
        thread.start()
        thread.join()

    def run(self):
        self.result = self.wrapper_loop.run_until_complete(self.co)


def wrap_as_sync(co: Coroutine):
    """
    run a coroutine in ANY context, and return its result.
    """
    return SyncWrapper(co)


def create_async_task(co: Coroutine):
    """
    start a coroutine asynchronously in ANY context, ignoring its result.
    """
    return loop.create_task(co)


def wait_for_async_task(task: asyncio.Task):
    return wrap_as_sync(asyncio.wait([task], loop=loop))()


def start_asyncio():
    global ref_count
    with ref_count_lock:
        if ref_count == 0:
            async_executor.start()
        ref_count = ref_count + 1


def stop_asyncio():
    global ref_count
    with ref_count_lock:
        ref_count = ref_count - 1
        if ref_count == 0:
            async_executor.stop()


def join_asyncio():
    async_executor.join()

ref_count = 0
ref_count_lock = threading.Lock()
async_executor: "AsyncExecutor" = AsyncExecutor()
loop = async_executor.loop
