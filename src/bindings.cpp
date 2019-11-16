#include <pybind11/pybind11.h>
#include "tlc59711.h"

namespace py = pybind11;

PYBIND11_MODULE(tlc59711, m) {
  py::class_<TLC59711>(m, "TLC59711")
          .def(py::init<std::uint8_t &>())
          .def("begin", &TLC59711::begin)
          .def("end", &TLC59711::end)
          .def("setPWM", &TLC59711::setPWM)
          .def("setLED", &TLC59711::setLED)
          .def("write", &TLC59711::write)
          .def("setBrightness", &TLC59711::setBrightness)
          .def("simpleSetBrightness", &TLC59711::simpleSetBrightness);
}
