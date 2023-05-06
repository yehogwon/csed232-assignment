import sys
import subprocess

if len(sys.argv) != 2: 
    exit(1)

test_cases = [
    ('119 2', '1110111'), 
    ('119 8', '167'), 
    ('119 16', '77')
]
    
check = True
for test_case, ans in test_cases: 
    if not check: 
        break
    out = subprocess.check_output([sys.argv[1]], input=test_case, encoding='utf-8')
    check = out.strip() == ans.strip()

exit(0 if check else 1)
