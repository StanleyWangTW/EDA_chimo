#include "include.hpp"
int main(int argc, const char** argv) {
    fstream fin;
    fstream fout;
    fin.open(argv[1], fstream::in);
    fout.open(argv[2], fstream::out);
    if (argc != 3) {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        exit(1);
    }
    if (!fin.is_open()) {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }
    if (!fout.is_open()) {
        cout << "Error : the output file is not opened!!" << endl;
        exit(1);
    }
    Weights weights;
    DieSize dieSize;
    vector<string> inputs;
    vector<string> outputs;
    vector<FlipFlop> flipFlops;
    vector<Instance> instances;
    vector<Net> nets;
    BinSize binSize;
    vector<PlacementRow> placementRows;
    vector<TimingSlack> timingSlacks;
    vector<GatePower> gatePowers;

    if (!parseInputFile(argv[1], weights, dieSize, inputs, outputs, flipFlops,
                        instances, nets, binSize, placementRows, timingSlacks,
                        gatePowers)) {
        cout << "Error: failed to parse input file!" << endl;
        exit(1);
    }
}