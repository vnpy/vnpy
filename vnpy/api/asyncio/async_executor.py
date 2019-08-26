"""
support for asyncio
If you use this module, call async_executor.start() at startup.
and call async_executor.stop() at cleanup.
call async_executor.join() if you want to wait until it exit.
"""
import asyncio
from threading import Thread
from typing import Coroutine


class AsyncExecutor:

    def __init__(self):
        self.loop = asyncio.new_event_loop()
        self._thread = Thread(target=self._exec)

        self.alive = False

    def start(self):
        self.alive = True
        self._thread.start()

    def stop(self):
        self.alive = False

    def join(self):
        self._thread.join()

    async def _run(self):
        while self.alive:
            await asyncio.sleep(1)

    def _exec(self):
        # run_forever seems not working well?
        self.loop.run_until_complete(self._run())


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
        thread = Thread(target=self.run)
        thread.start()
        thread.join()

    def run(self):
        self.result = self.wrapper_loop.run_until_complete(self.co)


def wrap_as_sync(co: Coroutine):
    return SyncWrapper(co)


async_executor: "AsyncExecutor" = AsyncExecutor()
loop = async_executor.loop
