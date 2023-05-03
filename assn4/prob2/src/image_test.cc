#include <cmath>
#include "SharedPtr.h"
#include "Image.h"

using namespace std;

void compute_edge_map(const Image<RGBf>& img, Image<RGBf>& edge_map)
{
	edge_map = Image<RGBf>(img.width(), img.height(), RGBf(.0f, .0f, .0f));
	for(int y = 0; y < img.height()-1; y++) {
		for(int x = 0; x < img.width()-1; x++) {
			for(int ch = 0; ch < 3; ch++) {
				float dx = img[y][x+1][ch] - img[y][x][ch];
				float dy = img[y+1][x][ch] - img[y][x][ch];
				edge_map[y][x][ch] = std::sqrt(dx*dx + dy*dy);
			}
		}
	}
}

void convert_rgb_to_gray(const Image<RGBf>& rgb, Image<float>& gray)
{
	gray = Image<float>(rgb.width(), rgb.height());
	for(int y = 0; y < rgb.height(); y++) {
		for(int x = 0; x < rgb.width(); x++) {
			gray[y][x] = (rgb[y][x].r + rgb[y][x].g + rgb[y][x].b)/3.0f;
		}
	}
}

void downsample(const Image<float>& img, Image<float>& downsampled, int scale_factor)
{
	size_t w = (img.width() + scale_factor-1) / scale_factor;
	size_t h = (img.height() + scale_factor-1) / scale_factor;
	Image<float> accum(w, h, 0.0f);
	Image<int> denom(w, h, 0);
	for(int y = 0; y < img.height(); y++) {
		for(int x = 0; x < img.width(); x++) {
			int y2 = y/scale_factor;
			int x2 = x/scale_factor;
			accum[y2][x2] += img[y][x];
			denom[y2][x2]++;
		}
	}

	downsampled = Image<float>(w, h);
	for(int y = 0; y < downsampled.height(); y++) {
		for(int x = 0; x < downsampled.width(); x++) {
			downsampled[y][x] = accum[y][x] / (float)denom[y][x];
		}
	}
}

void draw_ascii_art(const Image<float>& img)
{
	static const char letters[] = "`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
	const int n_letters = sizeof(letters) / sizeof(letters[0]);
	float minv, maxv;
	minv = maxv = img[0][0];
	for(int y = 0; y < img.height(); y++) {
		for(int x = 0; x < img.width(); x++) {
			if(img[y][x] > maxv) maxv = img[y][x];
			if(img[y][x] < minv) minv = img[y][x];
		}
	}
	for(int y = 0; y < img.height(); y++) {
		for(int x = 0; x < img.width(); x++) {
			int idx = static_cast<int>((img[y][x]-minv)*(maxv-minv) * static_cast<float>(n_letters-1));
			std::cout << letters[idx];
		}
		std::cout << std::endl;
	}
}

int main()
{
	Image<RGB8b> img;
	load_bmp("input.bmp", img);
	Image<RGBf> imgf;

	convert_pixel_type(img, imgf);

	/////////////////////////////////////////////////
	// simple image operations
	/////////////////////////////////////////////////
	
	//  1. Edge detection
	Image<RGBf> edge_map;
	compute_edge_map(imgf, edge_map);
	convert_pixel_type(edge_map, img);
	save_bmp("edge.bmp", img);

	std::cout << "2. ASCII conversion" << std::endl;
	//  2. ASCII conversion
	//     2.1. Grayscale conversion
	//     2.2. Downsampling
	//     2.3. ASCII conversion
	std::cout << "2.1. Grayscale conversion" << std::endl;
	Image<float> gray;
	convert_rgb_to_gray(imgf, gray);

	std::cout << "2.2. Downsampling" << std::endl;

	int scale_factor = 10;
	Image<float> downsampled;
	downsample(gray, downsampled, scale_factor);

	std::cout << "2.3. ASCII art drawing" << std::endl;
	draw_ascii_art(downsampled);
		
	return 0;
}
