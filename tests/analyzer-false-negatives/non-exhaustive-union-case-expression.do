// Invalid: a case expression over a class union must cover every member.
// expect-error: 6:50 Case expression must be exhaustive
class Circle { radius: double }
class Square { side: double }

function area(shape: Circle | Square): double => case shape {
    circle: Circle -> circle.radius
}
