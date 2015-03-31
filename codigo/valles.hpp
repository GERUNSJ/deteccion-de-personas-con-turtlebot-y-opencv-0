/*
 * valles.hpp
 *
 *  Created on: 15/05/2014
 *      Author: pablo
 */

#ifndef VALLES_HPP_

//Para 8 bits.


void encontrar_valles(cv::Mat& histograma, std::vector< std::vector<int> > &pares) {
    std::vector<int> par;
    std::vector<int>::iterator it1;
    std::vector< std::vector<int> >::iterator it2;
    int i = 0; //Valles
    int j = 0; //Pares de valles


    //Primer elemento
    par.push_back(0);

    for (i = 1; i < histograma.rows - 1; i++) //Del 1 al 254
    {
        if ((histograma.at<float>(i) <= histograma.at<float>(i - 1)) &&
                (histograma.at<float>(i) < histograma.at<float>(i + 1))) {
            j++;
            par.push_back(i);
            pares.push_back(par);
            par.erase(par.begin(), par.end());
            par.push_back(i);

        }
    }

    //Último elemento
    par.push_back(255);
    pares.push_back(par);

    for (it2 = pares.begin(); it2 != pares.end(); it2++) {
        par = *it2;

        std::cout << par.at(0) << '\t' << par.at(1) << '\n';
    }
    

    std::cout << '\n';

    std::cout << "\n\nHay " << j << " minimos y " << pares.size() << " pares.\n";

    return;
}
/*std::vector<int> encontrar_valles(cv::Mat& histograma)
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
*/


#define VALLES_HPP_




#endif /* VALLES_HPP_ */
