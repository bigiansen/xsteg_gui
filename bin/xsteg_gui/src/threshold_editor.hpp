#pragma once

#include <imgui.h>
#include <xsteg/availability_map.hpp>
#include <vector>

class threshold_editor
{
private:
    std::vector<xsteg::availability_threshold> _thresholds;

public:
    void update();
    size_t threshold_count();
    xsteg::pixel_availability truncated_bits();

    const std::vector<xsteg::availability_threshold>& thresholds();
    void thresholds(std::vector<xsteg::availability_threshold>&&);
};