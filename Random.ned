network RandomGraph
{
    parameters:
    	int totalNodes = default(5);
		double connectedness = default(0.3);
		int frequency = default(2);
    
    submodules:
        node[totalNodes]: Node{
	        id = index;
        	totalNodes = totalNodes;
        	frequency = frequency;
	    }
        
    connections:
        for i=0..totalNodes-2{
            node[i].g++ <--> node[i+1].g++;
        }
        for i=0..totalNodes-1,for j=i+2..totalNodes-1{
            node[i].g++ <--> node[j].g++ if uniform(0,1)<connectedness;
        }
}