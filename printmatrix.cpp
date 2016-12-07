#include "printmatrix.h" 
#include <iomanip>

std::ostream& operator<<(std::ostream& str, const QMatrix4x4& mat){

   str << "[" << std::endl;
   for(int row=0; row<4; row++){
     QVector4D r = mat.row(row);
     str << "["
       << std::setw(6) << std::setprecision(4) << r[0] << ", " 
       << std::setw(6) << std::setprecision(4) << r[1] << ", " 
       << std::setw(6) << std::setprecision(4) << r[2] << ", " 
       << std::setw(6) << std::setprecision(4) << r[3] << ", " 
       << " ]" << std::endl;
   }
   str << "]" << std::endl;
   return str;
}

