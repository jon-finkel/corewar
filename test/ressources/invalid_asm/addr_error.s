.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %toto, r1

live:	live %1
		zjmp %:live
