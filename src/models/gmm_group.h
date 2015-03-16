/*
 * gmm_group.h
 *
 * Group of Gaussian Mixture Models for continuous recognition and regression with multiple classes
 *
 * Contact:
 * - Jules Françoise <jules.francoise@ircam.fr>
 *
 * This code has been initially authored by Jules Françoise
 * <http://julesfrancoise.com> during his PhD thesis, supervised by Frédéric
 * Bevilacqua <href="http://frederic-bevilacqua.net>, in the Sound Music
 * Movement Interaction team <http://ismm.ircam.fr> of the
 * STMS Lab - IRCAM, CNRS, UPMC (2011-2015).
 *
 * Copyright (C) 2015 UPMC, Ircam-Centre Pompidou.
 *
 * This File is part of XMM.
 *
 * XMM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XMM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XMM.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef mhmm_concurrent_gmm_h
#define mhmm_concurrent_gmm_h

#include "model_group.h"
#include "gmm.h"

/**
 * @ingroup GMM
 * @class GMMGroup
 * @brief Set of GMMs Running in parallel
 * @details Allows to perform GMM-based pattern recognition.
 * @see ModelGroup
 */
class GMMGroup : public ModelGroup< GMM > {
public:
    /**
     * @brief Iterator over models
     */
    typedef map<Label, GMM>::iterator model_iterator;
    
    /**
     * @brief Constant Iterator over models
     */
    typedef map<Label, GMM>::const_iterator const_model_iterator;
    
#pragma mark > Constructors
    /*@{*/
    /** @name Constructors */
    /**
     * @brief Constructor
     * @param globalTrainingSet training set associated with the model
     * @param flags Construction Flags: use 'BIMODAL' for use with Gaussian Mixture Regression.
     */
    GMMGroup(rtml_flags flags = NONE,
                  TrainingSet *globalTrainingSet=NULL);
    
    /*@}*/

#pragma mark > Accessors
    /*@{*/
    /** @name Accessors */
    /**
     * @brief Get the number of Gaussian mixture Components
     * @return number of Gaussian mixture components
     */
    int get_nbMixtureComponents() const;
    
    /**
     * @brief Get Offset added to covariance matrices for convergence (Relative to data variance)
     * @return Offset added to covariance matrices for convergence
     */
    double get_varianceOffset_relative() const;
    
    /**
     * @brief Get Offset added to covariance matrices for convergence (Minimum value)
     * @return Offset added to covariance matrices for convergence
     */
    double get_varianceOffset_absolute() const;
    
    /**
     * @brief Set the number of mixture components of the model
     * @warning sets the model to be untrained.
     * @param nbMixtureComponents number of Gaussian Mixture Components
     * @throws invalid_argument if nbMixtureComponents is <= 0
     */
    void set_nbMixtureComponents(int nbMixtureComponents);
    
    /**
     * @brief Set the offset to add to the covariance matrices
     * @param varianceOffset_relative offset to add to the diagonal of covariance matrices (relative to data variance)
     * @param varianceOffset_absolute offset to add to the diagonal of covariance matrices (minimum value)
     * @throws invalid_argument if the covariance offset is <= 0
     */
    void set_varianceOffset(double varianceOffset_relative, double varianceOffset_absolute);
    
    /**
     * @brief Get Regression Weight
     * @return Weight of the regresion part for synthesis
     */
    double get_weight_regression() const;
    
    /**
     * @brief Get Regression Weight
     * @param weight_regression Weight of the regresion part for synthesis
     */
    void set_weight_regression(double weight_regression);
    
    /*@}*/

#pragma mark > Performance
    /*@{*/
    /** @name Performance */
    /**
     * @brief Main Play function: performs recognition (unimodal mode) and regression (bimodal mode)
     * @details The predicted output is stored in the observation vector in bimodal mode
     * @param observation observation vector
     */
    void performance_update(vector<float> const& observation);
    
    /*@}*/

#pragma mark > JSON I/O
    /*@{*/
    /** @name JSON I/O */
    /**
     * @brief Write to JSON Node
     * @return JSON Node containing training set information and data
     */
    virtual JSONNode to_json() const;
    
    /**
     * @brief Read from JSON Node
     * @param root JSON Node containing training set information and data
     * @throws JSONException if the JSON Node has a wrong format
     */
    virtual void from_json(JSONNode root);
    
    /*@}*/
};


#endif
