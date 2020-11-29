#pragma once

#include <memory>
#include <vector>

#include "raytracer/hittable.h"

class HittableList : public Hittable {
    public:
        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object) { Add(object); }

        void Clear() { objects_.clear(); }
        void Add(std::shared_ptr<Hittable> object) { objects_.push_back(object); }

        virtual bool Hit(const Ray&, double, double, HitRecord&) const override;

    private:
        std::vector<std::shared_ptr<Hittable>> objects_;
};

bool HittableList::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects_) {
        if (object->Hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
