#include "QuadTree.hpp"
#include "GLOBALS.hpp"
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>

QuadTree::QuadTree(GLuint width, GLuint minWidth) {
  m_nodeCounter = 0;
  MIN_QUAD_SIZE = minWidth;
  m_rootNode = new Node();
  GenerateTree(nullptr, m_rootNode, 0, 0, width);
  //std::cout << "\nTree generation finished." << '\n';
}

//  Input a node*, init node and connect 4 new nodes until highest resolution is met
void QuadTree::GenerateTree(Node* parentNode, Node* nodePtr, GLuint xPos, GLuint zPos, GLuint width) {
  // Init current node
  nodePtr->s_id = m_nodeCounter++;
  nodePtr->s_parent = parentNode;
  nodePtr->s_x = xPos;
  nodePtr->s_z = zPos;
  nodePtr->s_width = width;
  nodePtr->s_isLeaf = false;
  nodePtr->s_insideFrustum = true;

  // if (nodePtr->s_parent != nullptr)
   // std::cout << "New node, id: " << nodePtr->s_id << " with parent, id: " << nodePtr->s_parent->s_id <<'\n';

  // check if it has reached highest resolution
  if (width <= MIN_QUAD_SIZE) {
    nodePtr->s_isLeaf = true;

    // std::cout << "nodeID: " << nodePtr->s_id << " is a leaf" << '\n';

    // Make children nullptr
    for (size_t i = 0; i < NUM_OF_NODES; i++) {
      nodePtr->s_children[i] = nullptr;
    }
    // Then stop generating more nodes
    return;
  }
  else {
    //std::cout << '\n';
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

void QuadTree::ReleaseNode(Node* currentNode) {
  if (!currentNode->s_isLeaf) {
    for (size_t i = 0; i < NUM_OF_NODES; i++) {
        ReleaseNode(currentNode->s_children[i]);
      }
  }
  else {
      delete currentNode;
  }
}

bool QuadTree::IsPointInNode(glm::vec3 point, Node* nodePtr) {
  glm::vec3 nodePos((float)nodePtr->s_x, 0, (float)nodePtr->s_z);
  float nodeWidth = (float)nodePtr->s_width;
  // std::cout << "IsPointInNode: " << point.x << ", "<< point.y << ", " << point.z;
  if (point.x <= (nodePos.x + nodeWidth) &&
      point.x >= nodePos.x &&
      point.z <= (nodePos.z + nodeWidth) &&
      point.z >= nodePos.z) {
      // std::cout << " Is in nodeID: " << nodePtr->s_id << '\n';
          return true;
  }
  else {
  // std::cout << " Is NOT in nodeID: " << nodePtr->s_id << '\n';
  return false;
  }
}

void QuadTree::InsertModelInTree(ModelData* modeldata) {
  int correctIndex = -1;
  // Get a point of model
  glm::vec4 modelPos = glm::column(modeldata->s_modelMat, 3);

  // compare model with node pos to determine best locataion for model
  Node* currentNodePtr = m_rootNode;
  bool correctChildFound = false;

  // if model is in bounds of QuadTree
  if (IsPointInNode(glm::vec3(modelPos), currentNodePtr)) {
    // Go down the tree until leafnode
    while (!currentNodePtr->s_isLeaf) {
      for (int i = 0; i < 4 && !correctChildFound; i++) {
        correctChildFound = IsPointInNode(glm::vec3(modelPos), currentNodePtr->s_children[i]);
        // if (correctChildFound) {
        //   std::cout << "currentNodePtr->s_children[" << i<< "] is corrent, id: " << currentNodePtr->s_children[i]->s_id << '\n';
        // }
        correctIndex = i;
      }
      // Step a node lower
      correctChildFound = false; // reset flag to find correct child node
      // std::cout << "Therefore inserrting in currentNodePtr->s_children[" << correctIndex<< "] is corrent, id: " << currentNodePtr->s_children[correctIndex]->s_id << ", parentID: " << currentNodePtr->s_id << '\n';
      currentNodePtr = currentNodePtr->s_children[correctIndex];
    }

  // finally insert model in correct leafnode
  currentNodePtr->s_models.push_back(modeldata);
  //std::cout << "Inserting model into NodeID: " << currentNodePtr->s_id << ", InsideFrustrum: "<< currentNodePtr->s_insideFrustum << ", modelsCount: "<< currentNodePtr->s_models.size() << '\n';
  }
}

QuadTree::~QuadTree() {
  ReleaseNode(m_rootNode);
}

void QuadTree::FillModelPack(Node* nodePtr) {
  // std::cout << "Attempting to fill modelPack with NodeID: " << nodePtr->s_id << "in frustum?, " << nodePtr->s_insideFrustum << '\n';
  if (nodePtr->s_insideFrustum && nodePtr->s_isLeaf) {
    if (nodePtr->s_models.size() != 0) {
      // std::cout << "Filling modelPack with nodeID: " << nodePtr->s_id << " because it in frustum " << nodePtr->s_insideFrustum << '\n';
      m_modelPack.insert(std::end(m_modelPack), std::begin(nodePtr->s_models), std::end(nodePtr->s_models));
    }
  }
  else if (nodePtr->s_insideFrustum && !nodePtr->s_isLeaf) {
    FillModelPack(nodePtr->s_children[TOP_LEFT]);
    FillModelPack(nodePtr->s_children[TOP_RIGHT]);
    FillModelPack(nodePtr->s_children[BOTTOM_LEFT]);
    FillModelPack(nodePtr->s_children[BOTTOM_RIGHT]);
  }
  else {
    return;
  }
}

void QuadTree::ClearModelPack() {
  m_modelPack.clear();
}

Node* QuadTree::GetRootNode() {
  return m_rootNode;
}

std::vector<ModelData*> QuadTree::GetModelPack() {
  return m_modelPack;
}
