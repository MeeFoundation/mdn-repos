import XCTest
import SwiftTreeSitter
import TreeSitterMeeQl

final class TreeSitterMeeQlTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_mee_ql())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading MeeQl grammar")
    }
}
