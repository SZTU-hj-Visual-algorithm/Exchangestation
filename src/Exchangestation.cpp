//
// Created by fly on 22-12-29.
//
#include "Exchangestation.h"
#include <vector>
void station::setinfo(cv::Mat image, int realcolor) {
    src=image;
    color=realcolor;
}
void station::changeMat(cv::Mat image) {
    src=image;
}

Mat station::pre_img(){
   // Mat gray;
  //  cvtColor(src, gray, COLOR_BGR2GRAY);
    vector<Mat> split_mats;
    split(src, split_mats);
    Mat dst;
    Mat binary;
    if (color==Red)
    {
        //�һ�վ����ɫ��ֵҪ�и�����Դ����������������Ҫ���е���
        dst = split_mats[2];
        threshold(dst, binary, 200, 255, THRESH_BINARY);
        imshow("dst", dst);
    }

    else {
        //������ɫ����ֵ�ȴ�����
        dst = split_mats[0];
        threshold(dst, binary, 150, 255, THRESH_BINARY);
        imshow("dst", dst);
    }
    //��Ϊ����Ҫ�õ��ر�׼ȷ�ģ�������Ҫ��������ǰ�ƶ���һ���쳣�����ϲ����ֽ���
    double _count = (double)getTickCount();
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    cout<<"dilate_time is: "<<((double)getTickCount() - _count)/1000<<endl;
    dilate(binary, binary, kernel);
    //waitKey(500);
    return binary;
}

Point2f station::process(float *tr)
{
    Mat test = src;
    Point2f result;
    if(src.empty()) {
        result.x=0;
        result.y=0;//TODO ����֮����Ը�Ϊһ�������������������λ��
        return result;
    }
    Mat binary= pre_img();

    imshow("binary",binary);
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    double _count = (double)getTickCount();
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cout<<"CONTOURS_time is: "<<((double)getTickCount() - _count)/1000<<endl;
#ifdef DRAW_CONTOURS
    for (int i = 0; i < contours.size(); i++)
		cv::drawContours(src, contours[i], i, Scalar(255, 0, 0), 2, LINE_8);
	imshow("contours_src", src);
#endif
    if (contours.size()<4){
        result.x=0;
        result.y=0;
        return result;
    }
    //tuple<vector<Point>, vector<int>> circle_conner;
    vector<Point> conPoly;
    vector<vector<Point>> four_contours;
    vector<Point> pts_24;
    for (int i = 0; i < contours.size(); i++)//��������������һ��������ж�����Ŀ�����
    {
        int area = contourArea(contours[i]);//����������
        if (area < 300) continue;
        //cout << area << endl;

        float peri = arcLength(contours[i], true);
        //peri�Ǹ�������parameter��arcLength���������ܳ������߳��ȣ�����������������պϡ�
        approxPolyDP(contours[i], conPoly, 0.03 * peri, true);
        //��ָ�����ȱƽ���������ߡ� conPoly���������������true��������������Ϊ���ǹر�
        if (conPoly.size() == 6)
        {
            //������������
            for (int i = 0; i < 6; i++) {
                if (i != 5) {
                    line(test,conPoly[i],conPoly[i+1],Scalar(255,0,200),2);
                }
                else {
                    line(test, conPoly[i], conPoly[0], Scalar(255, 0, 200),2);
                }
            }
            four_contours.push_back(conPoly);
        }
    }
    imshow("test", test);

    float radius;
    vector<Point2f> centers;
    Point2f center;
    if(four_contours.size()<4){
        result.x=0;
        result.y=0;
        return result;
    }

    for (int i = 0; i < four_contours.size(); i++)
    {
        minEnclosingCircle(four_contours[i], center, radius);
        circle(src, Point(center), static_cast<int>(radius), Scalar(255, 255, 0), 2);
        centers.push_back(center);
        //circle_conner = make_tuple<center, radius>;
        //cout << "center  " << center << "  radius" << radius << endl;
        //float area = contourArea(contours[i]);
        //cout << "number." << i << " is: " << area << endl;
    }

   //RotatedRect rec = minAreaRect(centers);

    //��Բ���
    float new_radius;
    minEnclosingCircle(centers,result,new_radius);
    *tr=new_radius*2;
    circle(src, Point(result), static_cast<int>(new_radius), Scalar(255, 255, 0), 2);
    Point2f vertex[4];
    //rec.points(vertex);
    /*for (int i = 0; i < 4; i++)
    {
        cv::line(test, vertex[i], vertex[(i + 1) % 4], cv::Scalar(100, 100, 200), 2);
    }*/
    circle(src, result, 5, Scalar(100, 200, 100),-1);
    //cout << "final_center is: " << result << endl;
    //for (int i = 0; i < contours.size(); i++)
    //drawContours(src, contours, i, Scalar(255, 0, 0), 2, LINE_8);
    //imshow("four_contours_src", src);

    for (int i = 0; i < four_contours.size(); ++i)
    {
        for (int j = 0; j < four_contours[i].size(); ++j)
        {
            //cout << four_contours[i].at(j) << "+";
        }
        //cout << endl;
    }

    putText(src, to_string(four_contours.size()), Point(0, 120), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 255, 255), 2, 8);
    imshow("src", src);
    waitKey(1);
    return result;
}