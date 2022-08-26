// keypoint_gen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <graphics/string_manip.h>
#include <QtCore/qdir.h>
#include <DistortionFunction.h>
#include <graphics/sys.h>


/*2022-08-26*/
//added by kiokahn
#include <string>
#include <vector>

#define RAPIDJSON_HAS_STDSTRING 1

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h" 

using namespace rapidjson;

#include "MakeKeypointJson.h"
/**/

#define max_cam_cnt 16

user::DistortionFunction* distortion_function[max_cam_cnt];
const int width_ = 1920;
const int height_ = 1080;

bool read_calib_file(std::string file_path)
{
	FILE* fp = fopen(file_path.c_str(), "r");
	char buffer[10000];
	int cnt = 0;

	if (!fp) {
		printf("there is no %s\n", file_path.c_str());
		return false;
	}
	while (fgets(buffer, 10000, fp)) {
		std::string str(buffer);
		std::vector<std::string> tokens;
		graphics::get_tokens(str, tokens, "\t,\n, ");
		if (tokens[0] == std::string("frame")) {
			cv::Mat cameraMatrix_ = cv::Mat::eye(3, 3, CV_64F);
			cv::Mat distCoeffs_ = cv::Mat::zeros(5, 1, CV_64F);
			double sw, sh, focal, cx, cy;

			fgets(buffer, 10000, fp);
			str = std::string(buffer);
			graphics::get_tokens(str, tokens, "\t,\n, ");
			sscanf(tokens[1].c_str(), "%lf", &sw);
			sscanf(tokens[2].c_str(), "%lf", &sh);

			fgets(buffer, 10000, fp);
			str = std::string(buffer);
			graphics::get_tokens(str, tokens, "\t,\n, ");
			sscanf(tokens[1].c_str(), "%lf", &focal);

			fgets(buffer, 10000, fp); // pixel Aspect
			fgets(buffer, 10000, fp);
			str = std::string(buffer);
			graphics::get_tokens(str, tokens, "\t,\n, ");
			sscanf(tokens[1].c_str(), "%lf", &cx);
			sscanf(tokens[2].c_str(), "%lf", &cy);

			fgets(buffer, 10000, fp); // distortionModel
			fgets(buffer, 10000, fp);
			str = std::string(buffer);
			graphics::get_tokens(str, tokens, "\t,\n, ");
			for (int i = 0; i < 5; i++)
				sscanf(tokens[i + 1].c_str(), "%lf", &distCoeffs_.at<double>(i, 0));

			fgets(buffer, 10000, fp); // corners

			graphics::vec3 org, up, right;
			fgets(buffer, 10000, fp);
			str = std::string(buffer);
			graphics::get_tokens(str, tokens, "\t,\n, ");
			sscanf(tokens[1].c_str(), "%lf", &org[0]);
			sscanf(tokens[2].c_str(), "%lf", &org[1]);
			sscanf(tokens[3].c_str(), "%lf", &org[2]);
			fgets(buffer, 10000, fp);
			str = std::string(buffer);
			graphics::get_tokens(str, tokens, "\t,\n, ");
			sscanf(tokens[1].c_str(), "%lf", &up[0]);
			sscanf(tokens[2].c_str(), "%lf", &up[1]);
			sscanf(tokens[3].c_str(), "%lf", &up[2]);
			fgets(buffer, 10000, fp);
			str = std::string(buffer);
			graphics::get_tokens(str, tokens, "\t,\n, ");
			sscanf(tokens[1].c_str(), "%lf", &right[0]);
			sscanf(tokens[2].c_str(), "%lf", &right[1]);
			sscanf(tokens[3].c_str(), "%lf", &right[2]);

			focal = (double(width_ - 1) / sw)*focal;
			cx = (double(width_ - 1)*0.5) + (double(width_ - 1) / sw)*cx;
			cy = (double(height_ - 1)*0.5) + (double(width_ - 1) / sw)*cy;
			cameraMatrix_.at<double>(0, 0) = focal;
			cameraMatrix_.at<double>(1, 1) = focal;
			cameraMatrix_.at<double>(0, 2) = cx;
			cameraMatrix_.at<double>(1, 2) = cy;

			//libmv::PinholeCamera cam;
			//matrix3x3 intrinsic = matrix3x3::identity();
			//for (int x = 0; x < 3; x++)
			//	for (int y = 0; y < 3; y++)
			//		intrinsic(x, y) = cameraMatrix_.at<double>(x, y);

			//matrix3x3 R;
			//vec3 x_dir = unit(right);
			//vec3 y_dir = unit(-up);
			//vec3 z_dir = unit(cross(x_dir, y_dir));
			//y_dir = cross(z_dir, x_dir);
			//R(0, 0) = x_dir[0];
			//R(0, 1) = x_dir[1];
			//R(0, 2) = x_dir[2];
			//R(1, 0) = y_dir[0];
			//R(1, 1) = y_dir[1];
			//R(1, 2) = y_dir[2];
			//R(2, 0) = z_dir[0];
			//R(2, 1) = z_dir[1];
			//R(2, 2) = z_dir[2];
			////R = R.inverse();
			//vec3 t = R * org*-1;
			//t = org;
			//cam.SetExtrinsicParameters(R, t);
			//vec2 principal(intrinsic(0, 2), intrinsic(1, 2));
			//cam.SetIntrinsicParameters(intrinsic(0, 0), principal);
			distortion_function[cnt] = new user::DistortionFunction;
			
			distortion_function[cnt]->init(cameraMatrix_, distCoeffs_, width_, height_);
			cnt++;
		}
	}
	fclose(fp);
	return true;
}
bool read_time_tables(FILE* fp, std::wstring& header, std::vector<float>& times)
{
	times.clear();
	char buffer[10000];
	fgets(buffer, 10000, fp);
	int num_of_times;
	sscanf(buffer, "%d", &num_of_times);
	fgets(buffer, 10000, fp);
	std::vector<std::string> tokens;
	graphics::get_tokens(std::string(buffer), tokens, "\n");

	header = graphics::to_utf16(tokens[0]);

	for (int i = 0; i < num_of_times; i++) {
		fgets(buffer, 10000, fp);
		float tmp;
		sscanf(buffer, "%f", &tmp);
		times.push_back(tmp);
	}
	return true;
}

bool read_directories(char* dir_name, std::vector<std::wstring>& dirs)
{
	dirs.clear();
	QDir dir(dir_name);

	dir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	dir.setSorting(QDir::Name);

	QStringList labels = dir.entryList();

	for (int i = 0; i < labels.size(); i++) {
		std::wstring a = labels[i].toStdWString();
		dirs.push_back(a);
	}
	return true;
}
bool read_files(const char* dir_name, std::vector<std::wstring>& files)
{
	files.clear();
	QDir dir(dir_name);

	dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	dir.setSorting(QDir::Name);

	QStringList labels = dir.entryList();

	for (int i = 0; i < labels.size(); i++) {
		//std::string tmp(dir_name);
		//tmp = tmp + "/";
		//std::wstring wtmp = graphics::to_utf16(tmp);
		std::wstring a = labels[i].toStdWString();
		files.push_back(a);
	}
	return true;
}

std::wstring camera_file(int cam_id, std::vector<std::wstring> files)
{
	std::wstring ret;
	for (int i = 0; i < files.size(); i++) {
		std::wstring name, ext;
		graphics::SeparateNameAndExt(files[i], name, ext);
		std::wstring digit;
		digit.resize(2);
		digit[0] = name[name.size() - 2];
		digit[1] = name[name.size() - 1];
		std::string digit8 = graphics::to_utf8(digit);
		int num = std::atoi(digit8.c_str());
		if (num == cam_id) {
			return files[i];
		}
	}
	return ret;
}
void form_string(std::wstring person, std::vector<std::string>& tokens, std::string& out)
{
	out = tokens[0] + "," + graphics::to_utf8(person);
	for (int i = 1; i < tokens.size() ; i++) {
		out = out + "," + tokens[i];
	}
}
std::string form_string_from_time(float f, FILE*fp, std::wstring person)
{
	char buffer[10000];
	float min_diff = 1000000.0;

	std::string ret_string;
	while (fgets(buffer, 10000, fp)) {
		std::vector<std::string> tokens;
		graphics::get_tokens(std::string(buffer), tokens, ",");
		float t;
		sscanf(tokens[0].c_str(), "%f", &t);
		float cur_dif = fabs(t - f);
		if (cur_dif < 0.1) {
			form_string(person, tokens, ret_string);
			return ret_string;
		}

		if (t > f + 0.1) return ret_string;
		//if (cur_dif < min_diff) {
		//	min_diff = cur_dif;
		//	form_string(person, tokens, ret_string);
		//}
	}
	return ret_string;
}
std::string form_header(std::string s)
{
	std::vector<std::string> tokens;
	graphics::get_tokens(s, tokens, ",\n");

	std::string out = tokens[0] + ",PersonName";
	for (int i = 1; i < tokens.size(); i++) {
		if (i > int(tokens.size() - 1) / 2) break; // this for reducing key
		out = out + "," + tokens[i];
	}
	return out;
}

bool read_data_and_write(std::wstring header, std::wstring idir, std::wstring odir, std::vector<std::wstring> persons, std::vector<float> time_table)
{

	std::vector<std::vector<std::wstring>> files(persons.size());
	std::vector<std::string> dirs;
	for (int i = 0; i < persons.size(); i++) {
		std::wstring sample_dir = idir + L"/" + persons[i];
		std::string  sample_dir8 = graphics::to_utf8(sample_dir);
		dirs.push_back(sample_dir8);
		read_files(sample_dir8.c_str(), files[i]);
	}
	char buffer[10000];
	for (int i = 0; i < max_cam_cnt; i++)
	{
		char num_design[5];
		sprintf(num_design, "%02d", i+1);
		std::string num_des_s(num_design);

		for (int t_table = 0; t_table < time_table.size(); t_table++) {
			std::string t_ = std::to_string(t_table+1);
			std::string odir_8  = graphics::to_utf8(odir);
			make_directory(odir_8.c_str());
			std::wstring cam_file_name = odir + L"/";//output csv file name
			std::wstring cam_file_name_json = odir + L"/";//output json file name  //added by kiokahn
			cam_file_name = cam_file_name + header + L"_T" + graphics::to_utf16(t_) +L"_"+ graphics::to_utf16(num_des_s)  + L".csv";
			cam_file_name_json = cam_file_name_json + header + L"_T" + graphics::to_utf16(t_) + L"_" + graphics::to_utf16(num_des_s) + L".json";//added by kiokahn

			//read csv files from captury export
			std::string header_from_csv;
			bool read_header = false;
			int person_cnt = 0;
			std::vector<std::string> out_string;
			for (int j = 0; j < persons.size(); j++) {
				std::wstring file_a = camera_file(i, files[j]);
				if (!file_a.empty()) {
					std::wstring input_file_name = idir + L"/" + persons[j] + L"/" + file_a;
					FILE* in_fp = _wfopen(input_file_name.c_str(), L"rt");
					fgets(buffer, 10000, in_fp);
					if (!read_header) {
						header_from_csv = std::string(buffer); 
						read_header = true;
					}
					std::string out_s = form_string_from_time(time_table[t_table], in_fp, persons[j]);
					if (!out_s.empty())out_string.push_back(out_s);
					fclose(in_fp);
				}
			}
			if (out_string.empty()) continue;

			/*
			//write csv format for frame images
			FILE* fp = _wfopen(cam_file_name.c_str(), L"wt");
			std::string header_tmp = graphics::to_utf8(header);
			fprintf(fp, "%s\n", header_tmp.c_str());
			fprintf(fp, "%d\n", out_string.size());
			header_tmp = form_header(header_from_csv);
			fprintf(fp, "%s\n", header_tmp.c_str());
			for (int j = 0; j < out_string.size(); j++) {
				std::vector<std::string> tokens;
				graphics::get_tokens(out_string[j], tokens," ;,\n");
				int point_count = (tokens.size() - 2) / 2 /2 ;//reduce key//;
				fprintf(fp, "%s,", tokens[0].c_str()); // Frames, # of frame
				fprintf(fp, "%s", tokens[1].c_str()); // PersonName, model id, person
				for (int k = 0; k < point_count; k++) {
					float v1, v2;
					sscanf(tokens[2 + k * 2 + 0].c_str(), "%f", &v1);
					sscanf(tokens[2 + k * 2 + 1].c_str(), "%f", &v2);
					graphics::vec2 out = distortion_function[i]->distort_point_by_map(graphics::vec2(v1, v2)*double(width_));
					fprintf(fp, ",%0.2f,%0.2f", out[0], out[1]);
				}
				fprintf(fp, "\n");
				//fprintf(fp, "%s", out_string[j].c_str());
			}
			fclose(fp);
			*/
			

			//write json format for frame images
			//added by kiokahn
			MakeKeypointJson make_json;

			ElementAnnotation ele_annotation;
			FILE* fp_json = _wfopen(cam_file_name_json.c_str(), L"wt");
			std::vector<std::string> keypoint_names;
			std::string json_header_tmp = form_header(header_from_csv);
			graphics::get_tokens(json_header_tmp, keypoint_names, ",\n");
			ele_annotation.time_unit_name = keypoint_names[0];
			keypoint_names.erase(keypoint_names.begin());// remove "Frames"
			keypoint_names.erase(keypoint_names.begin());// remove "PersonName"
			ele_annotation.keypoint_names = keypoint_names;// copy keypoints names

			for (int j = 0; j < out_string.size(); j++) {
				std::vector<std::string> tokens;
				graphics::get_tokens(out_string[j], tokens, " ;,\n");
				int point_count = (tokens.size() - 2) / 2 / 2;//reduce key//;
				//fprintf(fp_json, "%s,", tokens[0].c_str());
				ele_annotation.time_stamp = float(std::stod(tokens[0].c_str()));
				//fprintf(fp_json, "%s", tokens[1].c_str());
				ele_annotation.lable = tokens[1];

				for (int k = 0; k < point_count; k++) {
					float v1, v2;
					sscanf(tokens[2 + k * 2 + 0].c_str(), "%f", &v1);
					sscanf(tokens[2 + k * 2 + 1].c_str(), "%f", &v2);
					graphics::vec2 out = distortion_function[i]->distort_point_by_map(graphics::vec2(v1, v2) * double(width_));

					ele_annotation.keypoints.push_back(out);
					//fprintf(fp, ",%0.2f,%0.2f", out[0], out[1]);
				}
				//fprintf(fp, "\n");
				make_json.AddPose(&ele_annotation);
				ele_annotation.keypoints.clear();
			}

			make_json.AddAnnotation();
			make_json.FileWrite(fp_json);
			//fprintf(fp_json, "%s", json_str.c_str());
			fclose(fp_json);
		}
	}

	return true;
}
int main(int argc, char* args[])
{
	if (argc < 2) {
		printf("usage: keypoint_gen.exe heart_times.txt 2DKeypoints(CSV) output\n");
		printf("heart_times.txt contains time info to extract\n");
		printf("2DKeypoints(CSV) is a directory which contains the input csv files,\n");
		printf("note that you need separate the each person into each sub directory,\n");
		printf("output is the output directory\n");
		return 0;
	}

	FILE* fp = fopen(args[1], "rt");
	if (!fp) {
		return 0;
	}
	std::string calib_file_path(args[1]);
	calib_file_path = graphics::GetDirectoryPath(calib_file_path);
	calib_file_path = calib_file_path + "camera.calib";

	if (!read_calib_file(calib_file_path)) {
		return 0;
	}

	std::wstring header;
	std::vector<float> time_table;
	read_time_tables(fp, header, time_table);
	if (argc < 3) {
		return 0;
	}
	std::vector<std::wstring> input_persons;
	read_directories(args[2], input_persons);

	std::wstring input_dir = graphics::to_utf16(std::string(args[2]));
	if (argc < 4) {
		return 0;
	}
	std::wstring out_dir = graphics::to_utf16(std::string(args[3]));
	read_data_and_write(header, input_dir, out_dir, input_persons, time_table);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
