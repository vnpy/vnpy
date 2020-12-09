/*
 * Copyright 2019 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    04_oes_strerror_sample.c
 *
 * 打印错误号对应的错误信息
 *
 * @version 0.15.10     2019/12/30
 * @since   2019/12/30
 */


#include    <oes_api/oes_api.h>
#include    <sutil/string/spk_strings.h>


int
main(int argc, char *argv[]) {
    int32               errCode = 0;

    if (argc != 2 || ! argv[1]) {
        printf("Usage: oes_strerror <errno>\n");
        return -1;
    }

    SStr_Strtoi(argv[1], &errCode);
    printf("==> errno [%d] is : ['%s']\n",
            errCode, OesApi_GetErrorMsg(errCode));

    return 0;
}
