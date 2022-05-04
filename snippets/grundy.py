from functools import lru_cache

def mex(values):
  for candidate in range(len(values) + 1):
    if candidate not in values:
      return candidate

@lru_cache(None)
def grundy(state):
  values = set()
  for move in moves(state):
    values.add(grundy(move))
  return mex(values)
