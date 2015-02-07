module conditions;

import std.exception;

int condMethod()
{
  version(Condition1)
  {
    version(Condition2) return 0;
    else return 1;
  }
  else
  {
    version(Condition2) return 2;
    else return 3;
  }
}

void checkConditions()
{
    enforce(condMethod() == 0);
}
