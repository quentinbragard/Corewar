.name "Azendo"
.comment "FUUUUUSIIIIOOOOONNNNN!!!"

	sti r1, %:live, %1
	add r4, r2, r3
live:
	live %0
	zjmp %:live
