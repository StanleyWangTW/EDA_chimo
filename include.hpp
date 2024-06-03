#ifndef INCLUDE_H
#define INCLUDE_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
struct Weights {
    double alpha;
    double beta;
    double gamma;
    double lambda;
};
struct DieSize {
    int x1, y1, x2, y2;
};

struct Pin {
    std::string name;
    int x, y;
};

struct FlipFlop {
    int id;
    std::string type;
    int x, y, numPins;
    std::vector<Pin> pins;
};

struct Instance {
    std::string name;
    std::string type;
    int x, y;
};

struct Net {
    std::string name;
    int numPins;
    std::vector<std::string> pins;
};

struct BinSize {
    int width, height, maxUtil;
};

struct PlacementRow {
    int x, y, numSites, siteWidth, siteSpacing;
};

struct TimingSlack {
    std::string instance;
    std::string pin;
    double slack;
};

struct GatePower {
    std::string type;
    double power;
};

bool parseInputFile(const std::string& filename,
                    Weights& weights,
                    DieSize& dieSize,
                    std::vector<std::string>& inputs,
                    std::vector<std::string>& outputs,
                    std::vector<FlipFlop>& flipFlops,
                    std::vector<Instance>& instances,
                    std::vector<Net>& nets,
                    BinSize& binSize,
                    std::vector<PlacementRow>& placementRows,
                    std::vector<TimingSlack>& timingSlacks,
                    std::vector<GatePower>& gatePowers) {
    std::fstream fin(filename, std::fstream::in);
    if (!fin.is_open()) {
        std::cerr << "Error: the input file is not opened!!" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "Alpha") {
            iss >> weights.alpha;
        } else if (key == "Beta") {
            iss >> weights.beta;
        } else if (key == "Gamma") {
            iss >> weights.gamma;
        } else if (key == "Lambda") {
            iss >> weights.lambda;
        } else if (key == "DieSize") {
            iss >> dieSize.x1 >> dieSize.y1 >> dieSize.x2 >> dieSize.y2;
        } else if (key == "NumInput") {
            int numInputs;
            iss >> numInputs;
            for (int i = 0; i < numInputs; ++i) {
                std::getline(fin, line);
                inputs.push_back(line);
            }
        } else if (key == "NumOutput") {
            int numOutputs;
            iss >> numOutputs;
            for (int i = 0; i < numOutputs; ++i) {
                std::getline(fin, line);
                outputs.push_back(line);
            }
        } else if (key == "FlipFlop") {
            FlipFlop ff;
            iss >> ff.id >> ff.type >> ff.x >> ff.y >> ff.numPins;
            for (int i = 0; i < ff.numPins; ++i) {
                std::getline(fin, line);
                std::istringstream pinStream(line);
                Pin pin;
                pinStream >> key >> pin.name >> pin.x >> pin.y;
                ff.pins.push_back(pin);
            }
            flipFlops.push_back(ff);
        } else if (key == "NumInstances") {
            int numInstances;
            iss >> numInstances;
            for (int i = 0; i < numInstances; ++i) {
                Instance inst;
                std::getline(fin, line);
                std::istringstream instStream(line);
                instStream >> key >> inst.name >> inst.type >> inst.x >> inst.y;
                instances.push_back(inst);
            }
        } else if (key == "NumNets") {
            int numNets;
            iss >> numNets;
            for (int i = 0; i < numNets; ++i) {
                Net net;
                std::getline(fin, line);
                std::istringstream netStream(line);
                netStream >> key >> net.name >> net.numPins;
                for (int j = 0; j < net.numPins; ++j) {
                    std::getline(fin, line);
                    net.pins.push_back(line);
                }
                nets.push_back(net);
            }
        } else if (key == "BinWidth") {
            iss >> binSize.width;
        } else if (key == "BinHeight") {
            iss >> binSize.height;
        } else if (key == "BinMaxUtil") {
            iss >> binSize.maxUtil;
        } else if (key == "PlacementRows") {
            PlacementRow row;
            iss >> row.x >> row.y >> row.numSites >> row.siteWidth >>
                row.siteSpacing;
            placementRows.push_back(row);
        } else if (key == "DisplacementDelay") {
            double displacementDelay;
            iss >> displacementDelay;
        } else if (key == "QpinDelay") {
            std::string type;
            double delay;
            iss >> type >> delay;
        } else if (key == "TimingSlack") {
            TimingSlack ts;
            iss >> ts.instance >> ts.pin >> ts.slack;
            timingSlacks.push_back(ts);
        } else if (key == "GatePower") {
            GatePower gp;
            iss >> gp.type >> gp.power;
            gatePowers.push_back(gp);
        } else {
            std::cerr << "Unknown key: " << key << std::endl;
            return false;
        }
    }

    fin.close();
    return true;
}
#endif