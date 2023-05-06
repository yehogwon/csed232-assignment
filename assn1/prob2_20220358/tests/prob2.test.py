import sys
import subprocess

if len(sys.argv) != 2: 
    exit(1)

test_cases = [
    ('+ 1.35 2.47', '3.820'), 
    ('* 3.986 2.515', '10.025'), 
    ('/ 24.999 3.900', '6.410'), 
    ('- -101.35 2.47', '-103.820'), 
    ('square 4', '16'), 
    ('sqrt 4', '2')
]
    
check = True
for test_case, ans in test_cases: 
    if not check: 
        break
    out = subprocess.check_output([sys.argv[1]], input=test_case, encoding='utf-8')
    check = float(out.strip()) == float(ans.strip())

exit(0 if check else 1)
