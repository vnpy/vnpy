celery worker -c 2 -A vnpy.task.celery_app  -P eventlet -l debug -f celery.log
