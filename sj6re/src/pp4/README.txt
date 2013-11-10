Removed Scope and implemented its methods in other ast files.
Removed reference to scope.cc from makefile.

OUTPUTS AGAINST GIVEN:

FILES				OUTPUT SAME as *.out		DIFFERENCE VALID?

samples/bad10.decaf		No				Yes, GetColor is not defined for Unknown.
samples/bad11.decaf		Yes
samples/bad12.decaf		Yes
samples/bad1.decaf		Yes
samples/bad2.decaf		Yes
samples/bad3.decaf		Yes
samples/bad4.decaf		Yes
samples/bad5.decaf		Yes
samples/bad6.decaf		No				Yes, return is underlined in mine.
samples/bad7.decaf		Yes
samples/bad8.decaf		Yes
samples/bad9.decaf		No				Yes, only Pi underlined instead of Pi(10)
samples/matrix.decaf		Yes
samples/new.decaf		No				Yes, difference in underlining on error in line 10
samples/queue.decaf		Yes
samples/stack.decaf		Yes
samples/t10.decaf		Yes
samples/t12.decaf		Yes
samples/t13.decaf		No				No < ERROR>
samples/t1.decaf		Yes
samples/t2.decaf		Yes
samples/t3.decaf		Yes
samples/t4.decaf		Yes
samples/t5.decaf		Yes
samples/t6.decaf		Yes
samples/t7.decaf		Yes
samples/t9.decaf		Yes

