#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "PackageStructs.hpp"

class QuadTree {
public:
<<<<<<< HEAD
  QuadTree(GLuint width) {
    m_nodeCounter = 0;
    m_rootNode = new Node();
    GenerateTree(nullptr, m_rootNode, 0, 0, width);
  }

  //  Input a node*, init node and connect 4 new nodes until highest resolution is met
  void GenerateTree(Node* parentNode, Node* nodePtr, GLuint xPos, GLuint zPos, GLuint width) {
    // Init current node
    nodePtr->s_id = m_nodeCounter++;
    nodePtr->s_parent = parentNode;
    nodePtr->s_x = xPos;
    nodePtr->s_z = zPos;
    nodePtr->s_width = width;
    nodePtr->s_isLeaf = false;
    nodePtr->s_insideFrustum = true;

    std::cout << "New node, id: " << nodePtr->s_id;

    // check if it has reached highest resolution
    if (width <= MIN_QUAD_SIZE) { // width <= 32
      std::cout << "is a leaf!" << std::endl;
      nodePtr->s_isLeaf = true;

      // Make children nullptr
      for (size_t i = 0; i < NUM_OF_NODES; i++) {
        nodePtr->s_children[i] = nullptr;
      }
      // Then stop generating more nodes
      return;
    }
    else {
      std::cout << '\n';
      GLuint widthChild = nodePtr->s_width / 2;
      for (size_t i = 0; i < NUM_OF_NODES; i++) {
        nodePtr->s_children[i] = new Node();
      }

      GenerateTree(nodePtr, nodePtr->s_children[TOP_LEFT],     xPos,              zPos + widthChild, widthChild);
      GenerateTree(nodePtr, nodePtr->s_children[TOP_RIGHT],    xPos + widthChild, zPos + widthChild, widthChild);
      GenerateTree(nodePtr, nodePtr->s_children[BOTTOM_LEFT],  xPos,              zPos,              widthChild);
      GenerateTree(nodePtr, nodePtr->s_children[BOTTOM_RIGHT], xPos + widthChild, zPos,              widthChild);
    }
  }

  void ReleaseNode(Node* currentNode) {
    if (!currentNode->s_isLeaf) {
      for (size_t i = 0; i < NUM_OF_NODES; i++) {
          ReleaseNode(currentNode->s_children[i]);
        }
    }
    else {
        delete currentNode;
    }
  }

  bool IsPointInNode(glm::vec3 point, Node* nodePtr) {
    glm::vec3 nodePos((float)nodePtr->s_x, 0, (float)nodePtr->s_z);
    float nodeWidth = (float)nodePtr->s_width;

    if (point.x <= (nodePos.x + nodeWidth) &&
        point.x >= nodePos.x &&
        point.z <= (nodePos.z + nodeWidth) &&
        point.z >= nodePos.z) {
            return true;
    }
    else {
    return false;
    }
  }

  void InsertModelInTree(ModelData modeldata) {
    int correctIndex = -1;
    // Assume modeldatas vertecies are in World space
    glm::vec3 modelPos = modeldata.s_meshPos[0][0];
    // compare model with node pos to determine best locataion for model
    Node* currentNodePtr = m_rootNode;
    bool activeNode = false;
    while (!currentNodePtr->s_isLeaf) {
      for (int i = 0; i < 4 && !activeNode; i++) {
        activeNode = IsPointInNode(modelPos, currentNodePtr->s_children[i]);
        correctIndex = i;
      }
      currentNodePtr = currentNodePtr->s_children[correctIndex];
    }
    currentNodePtr->s_VAOs = modeldata.s_VAOs;
  }

  // TODO cull quadtree with frustum
  ~QuadTree() {
    ReleaseNode(m_rootNode);
  }
=======
  QuadTree(GLuint width);
  void GenerateTree(Node* parentNode, Node* nodePtr, GLuint xPos, GLuint zPos, GLuint width);
  void ReleaseNode(Node* currentNode);
  bool IsPointInNode(glm::vec3 point, Node* nodePtr);
  void InsertModelInTree(ModelData* modeldata);
  void FillModelPack(Node* nodePtr);
  ~QuadTree();
  std::vector<ModelData*> GetModelPack();
  void ClearModelPack();
  Node* GetRootNode();
>>>>>>> It culls not somewhat OK
private:
  const GLuint MIN_QUAD_SIZE = 16;
  GLuint m_nodeCounter;
  Node* m_rootNode;
  std::vector<ModelData*> m_modelPack;
};