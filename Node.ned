simple Node
{
    parameters:
            int x = intuniform(0,1000);
            int y = intuniform(0,1000);
            @display("p=$x,$y");
            int id = default(-1);
            int simlength = default(3600);
            int frequency = default(2);
            int totalNodes = default(-1);
        gates:
            inout g[];

}