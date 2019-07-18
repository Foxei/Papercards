/**
 * @author Simon Schaefer
 * @date 12.07.2019
 * @file ColorDefinitions.h
 */

#ifndef REALTIMEFLUID_COLORDEFINES_H
#define REALTIMEFLUID_COLORDEFINES_H

#include <QtGui/QColor>

/**
 * Contains all application colors
 */
namespace Color {
const QColor GREEN = QColor(80, 250, 123);
const QColor CYAN = QColor(2, 233, 253);
const QColor BLUE = QColor(98,114,164);
const QColor ORANGE = QColor(255, 184, 108);
const QColor PINK = QColor(255, 121, 198);
const QColor PURPLE = QColor(189, 147, 249);
const QColor RED = QColor(155, 85, 85);
const QColor YELLOW = QColor(241, 250, 140);
const QColor WHITE = QColor(248, 248, 242);
const QColor BACKGROUND = QColor(40,42,54);
const QColor BASE = QColor(68,71,90);
const QColor BLACK = QColor(10,10,10);
const QColor TRANSPARENT = QColor(0, 0, 0, 0);

/* All opengl Colors */
const QColor DIVERGENCE_FIRST = QColor(255, 10, 10);
const QColor DIVERGENCE_SECOND = QColor(10, 255, 10);
const QColor VELOCITY_FIRST = QColor(255, 10, 10);
const QColor VELOCITY_SECOND = QColor(10, 255, 10);
const QColor PRESSURE_FIRST = QColor(255, 10, 10);
const QColor PRESSURE_SECOND = QColor(10, 255, 10);
const QColor DENSITY = QColor(255, 10, 10);

}

#endif //PAPERCARDS_COLORDEFINITIONS_H
