#ifdef Serial_Debug_Enable
      
      
      #ifdef Memory_Debug
      
          int availableMemory() 
          {
                int byteCounter = 0; // initialize a counter
                byte *byteArray; // create a pointer to a byte array
                // More on pointers here: http://en.wikipedia.org/wiki/Pointer#C_pointers
              
                // use the malloc function to repeatedly attempt allocating a certain number of bytes to memory
                // More on malloc here: http://en.wikipedia.org/wiki/Malloc
                while ( (byteArray = (byte*) malloc (byteCounter * sizeof(byte))) != NULL ) {
                  byteCounter++; // if allocation was successful, then up the count for the next try
                  free(byteArray); // free memory after allocating it
                }
               
                free(byteArray); // also free memory after the function finishes
                return byteCounter; // send back the highest number of bytes successfully allocated
         }

        void SerialDebugMemoryUsage(){
              Serial.println(availableMemory()); 
        }
     
     #endif

     void SerialDebugStart(){
          Serial.begin(9600);
     }

    
     void SerialDebugPrint(String SerialDebugingMessage)
     {
          Serial.println(SerialDebugingMessage);
     }

     

#endif 
