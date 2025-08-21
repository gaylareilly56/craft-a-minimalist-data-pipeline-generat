#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Data Model
struct Connection {
    string from;
    string to;
    string type;
};

struct Node {
    string id;
    string name;
    vector<Connection> outputs;
};

struct Pipeline {
    vector<Node> nodes;
    vector<Connection> connections;
};

// Pipeline Generator
class PipelineGenerator {
public:
    Pipeline generatePipeline(map<string, string> config) {
        Pipeline pipeline;

        // Create nodes
        Node sourceNode = {"source", "Source", {}};
        Node transformNode = {"transform", "Transform", {}};
        Node sinkNode = {"sink", "Sink", {}};

        pipeline.nodes.push_back(sourceNode);
        pipeline.nodes.push_back(transformNode);
        pipeline.nodes.push_back(sinkNode);

        // Create connections
        Connection sourceToTransform = {"source", "transform", "stream"};
        Connection transformToSink = {"transform", "sink", "stream"};

        pipeline.connections.push_back(sourceToTransform);
        pipeline.connections.push_back(transformToSink);

        return pipeline;
    }
};

int main() {
    PipelineGenerator generator;

    map<string, string> config = {
        {"source", "file"},
        {"transform", "mapper"},
        {"sink", "console"}
    };

    Pipeline pipeline = generator.generatePipeline(config);

    // Print pipeline
    cout << "Pipeline:" << endl;
    for (auto node : pipeline.nodes) {
        cout << "  Node: " << node.id << " (" << node.name << ")" << endl;
        for (auto output : node.outputs) {
            cout << "    Output: " << output.to << " (" << output.type << ")" << endl;
        }
    }
    cout << "Connections:" << endl;
    for (auto connection : pipeline.connections) {
        cout << "  " << connection.from << " -> " << connection.to << " (" << connection.type << ")" << endl;
    }

    return 0;
}