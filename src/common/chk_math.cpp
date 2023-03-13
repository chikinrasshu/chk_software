#include "chk_math.h"

namespace chk
{
    vec2 scale_keep_aspect(vec2 src, vec2 dst)
    {
        /*
            aspect_ratio = original_aabb.width / original_aabb.height
            target_aspect_ratio = target_aabb.width / target_aabb.height
            if aspect_ratio == target_aspect_ratio:
                scale_factor = target_aabb.width / original_aabb.width
            else:
                if aspect_ratio < target_aspect_ratio:
                    # Scale along the height axis
                    scale_factor = target_aabb.height / original_aabb.height
                else:
                    # Scale along the width axis
                    scale_factor = target_aabb.width / original_aabb.width
            scaled_aabb.width = original_aabb.width * scale_factor
            scaled_aabb.height = original_aabb.height * scale_factor
            scaled_aabb.center = target_aabb.center
        */

        auto src_ratio = src.x / src.y;
        auto dst_ratio = dst.x / dst.y;
        auto scale = 1.0f;

        if (src_ratio == dst_ratio)
        {
            scale = dst.x / src.x;
        }
        else
        {
            if (src_ratio < dst_ratio)
                scale = dst.y / src.y;
            else
                scale = dst.x / src.x;
        }

        auto scaled = src * scale;
        return scaled;
    }
}