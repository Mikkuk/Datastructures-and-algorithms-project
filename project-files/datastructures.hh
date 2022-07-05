// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <map>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();
    // Estimate of performance: O(1)
    // Short rationale for estimate: The counter is updated as new members are added.
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on map size n
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on the amount of keys (n) in map
    std::vector<PlaceID> all_places();

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: inserting map items into another (empty) map
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: Uses std::sort  where time complexity is O(nlog(n))
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on the amount of keys (n) in map
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on the amount of keys (n) in map
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: Two operations where time complexity is O(log(n))
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    Name get_area_name(AreaID id);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on the amount of keys (n) in map
    std::vector<AreaID> all_areas();

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: With the recursive function time complexity is O(n)
    // Short rationale for estimate: Parentareas are checked recursively so performance depends on
    // the amount of areas n
    std::vector<AreaID> subarea_in_areas(AreaID id);

    //recursive helper function that subarea_in_areas() uses
    void check_parentareas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance: With the recursive function time complexity is O(n)
    // Short rationale for estimate: Subareas are checked recursively so performance depends on
    // the amount of subareas n
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    //helper function that all_subareas_in_areas() uses
    void check_subareas(AreaID id);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: Uses std::sort  where time complexity is O(nlog(n))
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map
    bool remove_place(PlaceID id);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: Two operations (std::sort) where time complexity is O(nlog(n))
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on the amount of keys (n) in map
    std::vector<WayID> all_ways();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Because of for loop depends on the amount of coords (n)
    bool add_way(WayID id, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Because of for loop depends on the amount of keys (n) in map
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);

    // Estimate of performance: Average for unordered_map O(1), worst case O(n)
    // Short rationale for estimate: Elements are stored internally as Balanced Binary Search tree
    // so above is the estimate of performance when using unordered_map::find
    std::vector<Coord> get_way_coords(WayID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on map size n
    void clear_ways();

    // Estimate of performance: O(V+E) (DFS-algorithm)
    // Short rationale for estimate: V is the number of vertices and E is the number of edges in the graph.
    // Maximum loop amount for While-loop is O(V). Maximum loop amount for For-loop is O(E). So the time
    // complexity for the whole algorithm is O(V+E).
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);

    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Because of for loop depends on the amount of connections (n)
    // crossroad has.
    bool remove_way(WayID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_least_crossroads(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID>> route_with_cycle(Coord fromxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_shortest_distance(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_ways();

private:
    // Add stuff needed for your class implementation here

    struct place{
        Name name;
        PlaceType place_type;
        Coord coord;
    };

    struct area{
        AreaID id;
        Name name;
        std::vector<Coord> coords;
        std::vector<area*> subareas;
        area* parent_area;
    };

    std::unordered_map<PlaceID, place> places_;
    std::unordered_map<PlaceID, area> areas_;
    std::vector<AreaID> parent_areas;
    std::vector<AreaID> sub_areas;

    //datastructure for ways and crossroads

    // W=White, G=Gray, B=Black
    enum node {W, G, B};

    struct way{
        WayID id = NO_WAY;
        std::vector<Coord> coords = {};
        Distance distance = NO_DISTANCE;
    };

    struct Crossroad{
        Coord coords = NO_COORD;
        std::vector<std::pair<Crossroad*, way*>> connections = {};
        node colour = W;
        Crossroad* last_crossroad = nullptr;
    };


    std::unordered_map<WayID, way> ways_;
    std::unordered_map<Coord, Crossroad, CoordHash> crossroads_;


};

#endif // DATASTRUCTURES_HH
