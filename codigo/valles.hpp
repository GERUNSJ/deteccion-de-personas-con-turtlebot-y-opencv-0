/*
 * valles.hpp
 *
 *  Created on: 15/05/2014
 *      Author: pablo
 */

#ifndef VALLES_HPP_

//Para 8 bits.
std::vector<int> encontrar_valles(cv::Mat& histograma)
{
	std::vector<int> valles;
	std::vector<int>::iterator it;
	int i = 0;

	//Primer elemento
	valles.push_back(0);

	for(i=1; i < histograma.rows-1 ; i++)	//Del 1 al 254
	{

		if(	(histograma.at<float>(i) <= histograma.at<float>(i-1)) &&
			(histograma.at<float>(i) < histograma.at<float>(i+1)) )
			{
				//std::cout << "\n" << histograma.at<float>(i-1) << " > " << histograma.at<float>(i) << " < " << histograma.at<float>(i+1);
				valles.push_back(i);
			}
	}

	//Último elemento
	valles.push_back(255);


	for(it = valles.begin(); it != valles.end() ; it++)
	{
		std::cout << ' ' << *it;
	}
	std::cout << '\n';

	std::cout << "\n\nHay " << valles.size() << " minimos.\n";

	return valles;
}



#define VALLES_HPP_




#endif /* VALLES_HPP_ */
