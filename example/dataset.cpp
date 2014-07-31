/*
 * Copyright © 2013-2014 Felix Höfling
 *
 * This file is part of h5xx.
 *
 * h5xx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/multi_array.hpp>
#include <h5xx/h5xx.hpp>
#include <iostream>

typedef boost::multi_array<int, 3> array_t;

void write_dataset(std::string const& filename, array_t const& array)
{
    h5xx::file f(filename, h5xx::file::trunc);
    std::string name = "integer array";
    h5xx::dataset d;
    h5xx::create_dataset(d, f, name, array);
    h5xx::write_dataset(d, array);
}

void read_dataset(std::string const& filename)
{
    h5xx::file f(filename, h5xx::file::in);
    std::string name = "integer array";
    array_t array = h5xx::read_dataset<array_t>(f, name);
    // print array along second dimension
    for (unsigned int i = 0; i < array.shape()[1]; ++i) {
        std::cout << "/group/integer array[0, " << i << ", 0] = " << array[0][i][0] << std::endl;
    }
}

int main(int argc, char** argv)
{
    // take filename from command line
    if (argc <= 1) {
        std::cout << "Usage: example file.h5" << std::endl;
        return(-1);
    }

    // set-up data as Boost.MultiArray
    array_t array(boost::extents[2][3][2]);
    int data[] = {99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88};
    array.assign(data, data + sizeof(data) / sizeof(int));

    // write to HDF5 file
    write_dataset(argv[1], array);

    // read from HDF5 file
    read_dataset(argv[1]);

    return 0;
}
