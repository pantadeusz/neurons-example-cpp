/**
 * Neural network example byy Tadeusz Puźniakowski, 2019
 * 
 * MIT license
 * */

// compile with: g++ nntest.cpp -std=c++14

#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include <cmath>

using namespace  std;

struct neuron {
    double s; // wartość wzbudzenia neuronu
    vector <int> inputs; // numery ID neuronów wejściowych
    vector <double> weights; // wagi wejść
    function<double(int, const map<int,neuron> &)> f; // funkcja aktywacji wraz z sumatorem
};

// wypisanie prostej sieci -- bez wag, po prostu połączenia
void print_nn(const map<int,neuron> &nn) {
    for (auto &e:nn) {
        cout << "neuron["<<e.first <<"]:" << "s:" << e.second.s << " wejscia: ";
        for (auto inp: e.second.inputs) {
            cout << inp << " ";
        }
        cout << endl;
    }
}
// obliczenie nowych wartości wzbudzenia wszystkich neuronów
map<int,neuron> calculate(const map<int,neuron> &nn) {
    map<int,neuron> ret = nn;
    for (auto neuron : nn) {
        // liczymy nową wartość na podstawie poprzedniej
        ret[neuron.first].s = nn.at(neuron.first).f(neuron.first, nn);
    }
    return ret;
}

int main() {
    double g = 0.5;
    map<int,neuron> neurons;
    auto f = [g](int id, const map<int,neuron> &nn) {
        double sum = 0;
        neuron n = nn.at(id);
        for (unsigned int i = 0; i < n.inputs.size(); i++) {
            sum += n.weights[i] * nn.at(n.inputs[i]).s;
        }
        return 1/(1+::exp(-g*sum)); // funkcja Fermiego
    };
    neurons[0] = {1,{},{},[](auto,auto){return 1;}}; // bias

    neurons[1] = {1,{0,2},{-0.7,-0.3},f};
    neurons[2] = {1,{1},{0.5},f};
    print_nn(neurons);
    neurons = calculate(neurons);
    print_nn(neurons);
    neurons = calculate(neurons);
    print_nn(neurons);
    neurons = calculate(neurons);
    print_nn(neurons);
    
    return 0;
}

