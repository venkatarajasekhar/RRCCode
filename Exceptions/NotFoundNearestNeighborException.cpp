#include "NotFoundNearestNeighborException.h"

NotFoundNearestNeighborException::NotFoundNearestNeighborException() {

}

const char *NotFoundNearestNeighborException::what() {
    return "Nearest neighbor not found exception!";
}

