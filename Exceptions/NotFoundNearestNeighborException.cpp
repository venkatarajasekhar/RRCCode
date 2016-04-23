#include "NotFoundNearestNeighborException.h"

NotFoundNearestNeighborException::NotFoundNearestNeighborException() {

}

const char *NotFoundNearestNeighborException::what() const noexcept {
    return "Nearest neighbor not found exception!";
}

