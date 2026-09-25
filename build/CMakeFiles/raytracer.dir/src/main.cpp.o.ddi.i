# 0 "/home/popcorn/project_programmer/programming/myproject-ray-tracing/src/main.cpp"
# 1 "/home/popcorn/project_programmer/programming/myproject-ray-tracing/build//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3
# 0 "<command-line>" 2
# 1 "/home/popcorn/project_programmer/programming/myproject-ray-tracing/src/main.cpp"
import std;
import vec3;

int main()
{

    constexpr double image_width{256};
    constexpr double image_hight{256};
    constexpr double maxColorValue{255.999};



    std::println("P3");
    std::println("{} {}", image_width, image_hight);
    std::cout << "255\n";


    for (int j{0}; j < image_hight; ++j)
    {
        for (int i{0}; i < image_width; ++i)
        {
            auto r = i / (image_width - 1);
            auto g = j / (image_hight - 1);
            auto b = 0.0;

            int ir = static_cast<int>(maxColorValue * r);
            int ig = static_cast<int>(maxColorValue * g);
            int ib = static_cast<int>(maxColorValue * b);

            std::println("{} {} {}", ir, ig, ib);
        }
    }
}
