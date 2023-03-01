const firstFollow = require('first-follow');

// const rules = [
//   // S -> a b A
//   {
//     left: 'S',
//     right: ['a', 'b', 'A']
//   },

//   // A -> b c
//   {
//     left: 'A',
//     right: ['b', 'c']
//   },

//   // A -> ε
//   {
//     left: 'A',
//     right: [null]
//   }
// ];

var fs = require('fs');
const rules = JSON.parse(fs.readFileSync('grammar.json', 'utf8'));

const { firstSets, followSets, predictSets } = firstFollow(rules);

var firstSetsJSON = JSON.stringify(firstSets);
fs.writeFile('firstSets.json', firstSetsJSON, err => {
    if (err) {
        console.log('Error writing file', err)
    } else {
        console.log('Successfully wrote file')
    }
})
console.log(firstSets);
/*
 *  // S: a
 *  // A: b, ε
 *
 *  {
 *    S: ['a'],
 *    A: ['b', null]
 *  }
 */

var followSetsJSON = JSON.stringify(followSets);
fs.writeFile('followSets.json', followSetsJSON, err => {
    if (err) {
        console.log('Error writing file', err)
    } else {
        console.log('Successfully wrote file')
    }
})
console.log(followSets);
/*
 *  // S: ┤
 *  // A: ┤
 *
 *  {
 *    S: ['\u0000'],
 *    A: ['\u0000']
 *  }
 */
var predictSetsJSON = JSON.stringify(predictSets);
fs.writeFile('predictSets.json', predictSetsJSON, err => {
    if (err) {
        console.log('Error writing file', err)
    } else {
        console.log('Successfully wrote file')
    }
})
console.log(predictSets);
/*
 *  // 1: a
 *  // 2: b
 *  // 3: ┤
 * 
 *  {
 *    '1': ['a'],
 *    '2': ['b'],
 *    '3': ['\u0000']
 *  }
*/