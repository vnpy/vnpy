#!/usr/bin/env bash

sphinx-build -b gettext . locale
sphinx-intl update -p locale -l zh-CN -l en