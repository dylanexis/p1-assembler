        lw      0       1       five        
        lw      0       2       neg1        
        add     1       2       3           
        nor     1       2       4          
        sw      0       3       result    
        beq     3       0       done       
        jalr    0       6                   
        noop                                
done    halt                                
five    .fill   5
neg1    .fill   -1
result  .fill   0
