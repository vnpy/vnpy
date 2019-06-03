from typing import Dict

import black

from autocxxpy.core.cxxparser import CxxFileParser

parser = CxxFileParser(
    files=["iTapAPIError.h",
           "TapAPIError.h",
           ],
    include_paths=['vntap/include']
)
result = parser.parse()
error_map: Dict[int, str] = {}
for v in result.g.variables.values():
    error_map[v.value] = v.brief_comment
for v in result.g.namespaces['ITapTrade'].variables.values():
    error_map[v.value] = v.brief_comment

result = f'error_map = {repr(error_map)}'

output_file = 'error_codes.py'
with open(output_file, "wt", encoding='utf-8') as f:
    f.write(result)
black.main([output_file])
