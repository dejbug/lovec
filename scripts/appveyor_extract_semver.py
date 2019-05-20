import os, re
x = re.search(r'\{(.+?)\}', os.getenv('APPVEYOR_REPO_COMMIT_MESSAGE'))
if not x: print ""
else: print x.group(1)
