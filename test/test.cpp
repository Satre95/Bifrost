#include <glm/glm.hpp>
#include "Bifrost.hpp"

int main() {
    Bifrost<glm::vec3, float> hashtable(4096, 2.f);
    float val1 = 1995.f;
    glm::vec3 key1(-14.f, 32.f, 100.f);
    hashtable.Insert(key1, val1);
    float val2 = 2000.f;
    glm::vec3 key2(-16.f, 32.f, 100.f);
    hashtable.Insert(key2, val2);

    std::vector<float> neighbors;
    hashtable.Neighbors(key1, neighbors);


    return 0;
}