module main;

import conditions;
import ddocChecker;
import enforceProperty;
import headerChecker;

import std.exception;

void main()
{
  checkConditions();
  checkDocs();
  checkProperties();
  checkHeaders();
}
