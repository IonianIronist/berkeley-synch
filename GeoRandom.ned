network RandomGeometricGraph
{
    parameters:
        int totalNodes = default(200);
    	int rc = default(400);
		int simlength = default(3600);
		int frequency = default(6);
    submodules:
        node[totalNodes]: Node{
            id = index;
            simlength = simlength;
            totalNodes = totalNodes;
            frequency = frequency;
            }
        
    connections:
        for i = 0..totalNodes-1, for j = i+1..totalNodes-1 //Gia kathe pithano zeugari komvwn
            {
                node[i].g++ <--> node[j].g++ if ((node[i].x-node[j].x)*(node[i].x-node[j].x) + (node[i].y-node[j].y)*(node[i].y-node[j].y)) < rc * rc;
            }
}