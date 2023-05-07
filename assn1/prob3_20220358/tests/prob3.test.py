import sys
import subprocess

if len(sys.argv) != 2: 
    exit(1)

test_cases = [
    ('+ 0X52 0b1000', '90'), 
    ('- 070 0XF', '41'), 
    ('* 0b10 031', '50'), 
    ('/ 0XFF 032', '9.808')
]
    
check = True

for test_case, ans in test_cases: 
    if not check: 
        break
    out = subprocess.check_output([sys.argv[1]], input=test_case, encoding='utf-8')
    check = float(out.strip()) == float(ans.strip())

exit(0 if check else 1)
