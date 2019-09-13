#pragma once

#include <guim/frame.hpp>
#include <xsteg/availability_map.hpp>
#include <vector>

class threshold_view : public guim::frame
{
private:
    xsteg::availability_threshold* _threshold = nullptr;    

public:
    bool delete_pending = false;
    int threshold_idx = -1;    

    threshold_view(
        const std::string& label, 
        xsteg::availability_threshold* thres,
        int thres_idx,
        ImVec2 size = ImVec2(0, 0));

    void update() override;
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

class threshold_editor : public guim::frame
{
private:
    std::vector<xsteg::availability_threshold> _thresholds;
    std::vector<threshold_view*> _threshold_views;
    bool _regen = true;
public:
    threshold_editor(const std::string& label, ImVec2 size = ImVec2(0, 0));
    void update() override;
};
