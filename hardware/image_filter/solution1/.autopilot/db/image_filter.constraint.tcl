set clock_constraint { \
    name clk \
    module image_filter \
    port ap_clk \
    period 6 \
    uncertainty 0.75 \
}

set all_path {}

set false_path {}
