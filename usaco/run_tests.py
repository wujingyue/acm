import sys
import subprocess

prob = sys.argv[1]
start = int(sys.argv[2])
end = int(sys.argv[3])

out_filename = '{}.out'.format(prob)
for i in range(start, end + 1):
  print 'Running test case {}...'.format(i)
  in_filename = '{}{}.in'.format(prob, i)
  ans_filename = '{}{}.out'.format(prob, i)
  with open(in_filename, 'r') as in_file:
    with open(out_filename, 'w') as out_file:
      subprocess.check_call(
          './{}'.format(prob), shell=True, stdin=in_file, stdout=out_file)
  subprocess.check_call(
      'diff -ruN {} {}'.format(out_filename, ans_filename), shell=True)
