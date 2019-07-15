/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file ViewContainer.h
 */

#ifndef PAPERCARDS_VIEWCONTAINER_H
#define PAPERCARDS_VIEWCONTAINER_H

/**
 * @brief Interface class that make all gui elements used in this project
 * homogeneous.
 * @details All gui elements should inheritance from this.
 */
class ViewContainer {
 private:

  /**
   * @brief All visible elements of this gui will be arrange and created in
   * this function.
   * @details
   */
  virtual void setupGui()=0;

  virtual void setupConnections()=0;
};

#endif //PAPERCARDS_VIEWCONTAINER_H
