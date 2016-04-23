#include "NotFoundNearestNeighborException.h"

NotFoundNearestNeighborException::NotFoundNearestNeighborException() {

}

const char *NotFoundNearestNeighborException::what() const {
    return "Nearest neighbor not found exception!";
}

