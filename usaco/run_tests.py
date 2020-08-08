import sys
import subprocess

prob = sys.argv[1]
start = int(sys.argv[2])
end = int(sys.argv[3])

out_filename = '{}.out'.format(prob)
for i in range(start, end + 1):
  print(f'Running test case {i}...')
  subprocess.check_call(f'cp {i}.in {prob}.in', shell=True)
  subprocess.check_call(f'./{prob}.exe', shell=True)
  subprocess.check_call(f'diff -qruN {prob}.out {i}.out', shell=True)
