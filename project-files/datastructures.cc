// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <stack>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::place_count()
{

    return places_.size();
}

void Datastructures::clear_all()
{

    places_.clear();
    areas_.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{

    std::vector<PlaceID> place_id_list;

    for (auto& place_id : places_)
       place_id_list.push_back(place_id.first);

    return place_id_list;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{

    if ( places_.find(id) != places_.end() ){
        return false;
    }

    place place_data;
    place_data.name = name;
    place_data.place_type = type;
    place_data.coord = xy;

    places_.insert(std::make_pair(id, place_data));

    return true;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{

    if ( places_.find(id) == places_.end() ) {
        return {NO_NAME, PlaceType::NO_TYPE};
    }

    return {places_[id].name, places_[id].place_type};
}

Coord Datastructures::get_place_coord(PlaceID id)
{

    if ( places_.find(id) == places_.end() ) {
        return NO_COORD;;
    }

    return places_[id].coord;
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{

    if ( areas_.find(id) != areas_.end() ){
        return false;
    }

    area area_data;
    area_data.id = id;
    area_data.name = name;
    area_data.coords = coords;
    area_data.subareas = {};
    area_data.parent_area = nullptr;

    areas_.insert(std::make_pair(id, area_data));

    return true;
}

Name Datastructures::get_area_name(AreaID id)
{

    if ( areas_.find(id) == areas_.end() ) {
        return NO_NAME;
    }

    return areas_[id].name;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{

    if ( areas_.find(id) == areas_.end() ) {
        return {NO_COORD};
    }

    return areas_[id].coords;
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{

    std::multimap<Name, PlaceID> sorted_by_name;
    std::vector<PlaceID> id_alphabetical_order;

    for (auto& place_id : places_)
        sorted_by_name.insert(std::make_pair(place_id.second.name, place_id.first));

    for (auto& name : sorted_by_name)
        id_alphabetical_order.push_back(name.second);

    return {id_alphabetical_order};
}


std::vector<PlaceID> Datastructures::places_coord_order()
{

    std::vector<PlaceID> id_coord_order;

    struct coords_data{
        double distance;
        PlaceID id;
        int y_coord;
    };
    coords_data coord;
    std::vector<coords_data> coords_data_list;

    struct {
        bool operator()(struct coords_data a, struct coords_data b)
                 //if distance is equal sort based on y coord
                const { if (a.distance == b.distance) {
                        return a.y_coord < b.y_coord; }

                return a.distance < b.distance; }
    }coordsort;

    for (auto& place_id : places_){
        int x = place_id.second.coord.x;
        int y = place_id.second.coord.y;
        double distance = std::sqrt(x*x + y*y);
        coord.distance = distance;
        coord.id = place_id.first;
        coord.y_coord = y;
        coords_data_list.push_back(coord);
    }

    std::sort(coords_data_list.begin(), coords_data_list.end(), coordsort);

    for (auto& i : coords_data_list){
        id_coord_order.push_back(i.id);
    }

    return {id_coord_order};
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{

    std::vector<PlaceID> id_list;

    for (auto& place_id : places_)
        if (place_id.second.name == name){
            id_list.push_back(place_id.first);
        }

    return {id_list};
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{

    std::vector<PlaceID> id_list;

    for (auto& place_id : places_)
        if (place_id.second.place_type == type){
            id_list.push_back(place_id.first);
        }

    return {id_list};
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{

    if(places_.find(id) != places_.end()){
        places_[id].name = newname;
        return true;
    }

    return false;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{

    if(places_.find(id) != places_.end()){
        places_[id].coord = newcoord;
        return true;
    }

    return false;
}

std::vector<AreaID> Datastructures::all_areas()
{

    std::vector<PlaceID> area_id_list;

    for (auto& area_id : areas_)
       area_id_list.push_back(area_id.first);

    return area_id_list;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{

    if (areas_.find(id) == areas_.end() or areas_.find(parentid) == areas_.end()){
        return false;
    }

    areas_[parentid].subareas.push_back(&areas_[id]);
    areas_[id].parent_area = &areas_[parentid];
    return true;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    if(areas_.find(id) == areas_.end()){
        return {NO_AREA};
    }

    parent_areas.clear();
    check_parentareas(id);
    return parent_areas;
}

void Datastructures::check_parentareas(AreaID id)
{
    if (areas_[id].parent_area == nullptr){
        return;
    }
    parent_areas.push_back(areas_[id].parent_area->id);
    check_parentareas(areas_[id].parent_area->id);
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{

    std::vector<PlaceID> id_close_places;

    struct coords_data{
        PlaceID id;
        double distance;
        int y_coord;
    };
    coords_data coord;

    std::vector<coords_data> coords_data_list;

    struct {
        bool operator()(struct coords_data a, struct coords_data b)
                 //if distance is equal sort based on y coord
                const { if( a.distance == b.distance) {
                        return a.y_coord < b.y_coord; }

                return a.distance < b.distance; }
    }coordsort;

    for (auto& place : places_){
        if (type != PlaceType::NO_TYPE){
            if (place.second.place_type == type){
                int x = xy.x;
                int y = xy.y;
                coord.id = place.first;
                double distance = std::sqrt(pow((x - place.second.coord.x), 2) + pow((y - place.second.coord.y), 2));
                coord.distance = distance;
                coord.y_coord = y;
                coords_data_list.push_back(coord);
            }
        }
        else {
            int x = xy.x;
            int y = xy.y;
            coord.id = place.first;
            double distance = std::sqrt(pow((x - place.second.coord.x), 2) + pow((y - place.second.coord.y), 2));
            coord.distance = distance;
            coord.y_coord = y;
            coords_data_list.push_back(coord);
        }
    }

    std::sort(coords_data_list.begin(), coords_data_list.end(), coordsort);

    if (coords_data_list.size() < 3 ){
        for (auto& i : coords_data_list){
            id_close_places.push_back(i.id);
        }
    }
    else {
        for (int i = 0; i < 3; i++){
            id_close_places.push_back(coords_data_list[i].id);
        }
    }
    return {id_close_places};
}

bool Datastructures::remove_place(PlaceID id)
{

    if ( places_.find(id) == places_.end() ) {
        return false;
    }

    std::unordered_map<PlaceID, place>::iterator it;
    it = places_.find(id);
    places_.erase(it);
    return true;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{

    if(areas_.find(id) == areas_.end()){
        return {NO_AREA};
    }

    sub_areas.clear();
    check_subareas(id);
    return sub_areas;
}

void Datastructures::check_subareas(AreaID id)
{
    if (areas_[id].subareas.empty()){
        return;
    }

    for(auto& sub_area : areas_[id].subareas){
        sub_areas.push_back(sub_area->id);
        check_subareas(sub_area->id);
    }
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{

    if (areas_.find(id1) == areas_.end()) {
        return NO_AREA;
    }

    if (areas_.find(id2) == areas_.end()) {
        return NO_AREA;
    }

    std::vector<AreaID> sub_areas1 = subarea_in_areas(id1);
    std::vector<AreaID> sub_areas2 = subarea_in_areas(id2);

    if (sub_areas1.empty()){
        return NO_AREA;
    }
    if (sub_areas2.empty()){
        return NO_AREA;
    }

    std::sort(sub_areas1.begin(), sub_areas1.end());
    std::sort(sub_areas2.begin(), sub_areas2.end());
    std::vector<AreaID>::iterator iterator1 = sub_areas1.begin();
    std::vector<AreaID>::iterator iterator2 = sub_areas2.begin();

    while(iterator1 != sub_areas1.end() or iterator2 != sub_areas2.end()){
        if (*iterator1 == *iterator2){
            return *iterator1;
        }
        else if (*iterator1 < *iterator2){
            iterator1++;
        }
        else if (*iterator1 > *iterator2){
            iterator2++;
        }
    }
    return NO_AREA;
}

std::vector<WayID> Datastructures::all_ways()
{
    std::vector<WayID> way_id_list;

    for (auto& way_id : ways_)
       way_id_list.push_back(way_id.first);

    return way_id_list;
}

bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{   

    struct {
        Distance operator()(Coord a, Coord b)
                 //Calculate the distance between two coords
                const { return sqrt(floor(pow((a.x - b.x), 2)) + floor(pow((a.y - b.y), 2))); }
    }calculateDistance;

    Distance distance = 0;
    for(unsigned int i = 1; i < coords.size(); i++){
        distance += calculateDistance(coords[i-1], coords[i]);
    }

    way new_way = {id, coords, distance};
    auto insertion_result = ways_.insert({id, new_way});
    if (!insertion_result.second){
        return false;
    }

    if(crossroads_.find(coords.front()) == crossroads_.end()) {
        Crossroad crossroad = {coords.front(), {}};
        crossroads_.insert({coords.front(), crossroad});
    }

    if(crossroads_.find(coords.back()) == crossroads_.end()) {
        Crossroad crossroad = {coords.back(), {}};
        crossroads_.insert({coords.back(), crossroad});
    }

    crossroads_[coords.front()].connections.push_back({&crossroads_[coords.back()], &ways_[id]});
    crossroads_[coords.back()].connections.push_back({&crossroads_[coords.front()], &ways_[id]});

    return true;
}

std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{
    std::vector<std::pair<WayID, Coord>> ways_from_coord = {};

    for (auto& way : ways_){
        if (way.second.coords.back() == xy){
            ways_from_coord.push_back({way.first, way.second.coords.front()});
        }
        else if (way.second.coords.front() == xy){
            ways_from_coord.push_back({way.first, way.second.coords.back()});
        }
    }
    return ways_from_coord;
}

std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    if (ways_.find(id) == ways_.end()){
        return {NO_COORD};
    }
    return ways_.at(id).coords;
}

void Datastructures::clear_ways()
{
    ways_.clear();
    crossroads_.clear();
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord fromxy, Coord toxy)
{

    if(crossroads_.find(fromxy) == crossroads_.end() or crossroads_.find(toxy) == crossroads_.end()){
        return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    }

    for (auto& crossroad : crossroads_){
        crossroad.second.last_crossroad = nullptr;
        crossroad.second.colour = W;
    }

    Crossroad* starting_point = &crossroads_[toxy];
    std::stack<Crossroad*> stack;
    Crossroad* uu;
    Crossroad* end_point;
    stack.push(starting_point);
    bool r_found = false;

    while (stack.empty() != true and r_found == false){
        uu = stack.top();
        stack.pop();
        if(uu->colour == W){
            uu->colour = G;
            stack.push(uu);
            for (auto& vv : uu->connections){
                if (vv.first->colour == W){
                    vv.first->last_crossroad = uu;
                    stack.push(vv.first);
                    if (vv.first->coords == fromxy){
                        r_found = true;
                        end_point = vv.first;
                        break;
                    }
                }
            }
        }
        else {
            uu->colour = B;
        }
    }
    if (r_found == false){
        return {};
    }

    Distance distance = 0;
    way* connecting_way;
    std::vector<std::tuple<Coord, WayID, Distance>> route;
    route.push_back({fromxy, NO_WAY, distance});
    while (end_point->coords != toxy){
        for (auto& connection : end_point->connections){
            if (connection.first == end_point->last_crossroad){
                connecting_way = connection.second;
            }
        }
        distance += connecting_way->distance;

        end_point = end_point->last_crossroad;
        route.push_back({end_point->coords, NO_WAY, distance});
    }
    return route;
}

bool Datastructures::remove_way(WayID id)
{

    std::unordered_map<WayID, way>::iterator it;
    it = ways_.find(id);
    if ( it == ways_.end() ) {
        return false;
    }

    auto first_coord = ways_.at(id).coords.front();
    auto last_coord = ways_.at(id).coords.back();

    way* way =  &ways_.at(id);
    Crossroad starting_point = crossroads_.at(first_coord);
    Crossroad end_point = crossroads_.at(last_coord);

    for (auto connection : starting_point.connections){
        if (connection.second == way){
            starting_point.connections.erase(std::remove(starting_point.connections.begin(),
                                                         starting_point.connections.end(), connection),
                                             starting_point.connections.end());
        }
    }

    for (auto connection : end_point.connections){
        if (connection.second == way){
            end_point.connections.erase(std::remove(end_point.connections.begin(),
                                                         end_point.connections.end(), connection),
                                             end_point.connections.end());
        }
    }

    ways_.erase(it);
    if (starting_point.connections.empty()){
        crossroads_.erase(starting_point.coords);
    }
    if (end_point.connections.empty()){
        crossroads_.erase(end_point.coords);
    }
    return true;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_least_crossroads(Coord fromxy, Coord toxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

std::vector<std::tuple<Coord, WayID> > Datastructures::route_with_cycle(Coord fromxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY}};
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_shortest_distance(Coord fromxy, Coord toxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

Distance Datastructures::trim_ways()
{
    // Replace this comment with your implementation
    return NO_DISTANCE;
}
