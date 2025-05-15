    	lw   0  0  loop
   	lw   0  1  mcand
   	lw   0  2  mplier
    	lw   0  3  result
	lw   0  4  neg1


loop 	beq  1  0  end
	

end  	halt

mcand 	.fill	6203
mplier 	.fill   1429
answer 	.fill 	0
neg1	.fill	-1
